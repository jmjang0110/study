#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"



CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
	, m_bIgnoreParentScale(false)
{

}

CTransform::~CTransform()
{

}



void CTransform::finalupdate()
{

	// Size x Rotation x Translation
	Matrix matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);
	Matrix matTranlation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);


	// 회전량 : radian 
	Matrix matRotX = XMMatrixRotationX(m_vRelativeRot.x);
	Matrix matRotY = XMMatrixRotationY(m_vRelativeRot.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRelativeRot.z); 
	Matrix matRotation = matRotX * matRotY * matRotZ;

	// World Matrix 생성 
	m_matWorld = matScale * matRotation * matTranlation; // [ S * R * T ]

	// 부모 오브젝트가 기준이다. 
	if (GetOwner()->GetParent())
	{
		Matrix m_matParentWorld = GetOwner()->GetParent()->Transform()->GetWorldMat();
		
		if (m_bIgnoreParentScale)
		{
			/*
				 부모 행렬의 Scale에  영향을 받지 않는다. 
			*/
			Vec3 vParentWorldScale = GetOwner()->GetParent()->Transform()->GetWorldScale();
			Matrix matParentScale = XMMatrixScaling(vParentWorldScale.x, vParentWorldScale.y, vParentWorldScale.z);
			Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);


			m_matWorld = m_matWorld * matParentScaleInv * m_matParentWorld;
		}
		else
		{
			/*
				 부모 행렬의 Scale에  영향을 받는다. 
			*/
			m_matWorld *= m_matParentWorld;
		}
		

	}


}




Vec3 CTransform::GetWorldScale()
{

	Vec3 vWorldScale = m_vRelativeScale;

	CGameObject* pParent = GetOwner()->GetParent();
	if (m_bIgnoreParentScale)
		pParent = nullptr;

	while (pParent)
	{
		vWorldScale *= pParent->Transform()->GetScale();

		bool bIgnoreParentScale = pParent->Transform()->m_bIgnoreParentScale;
		pParent = pParent->GetParent();

		if (bIgnoreParentScale)
			pParent = nullptr;
	}

	return vWorldScale;

}

void CTransform::UpdateData()
{
	// 필요한 데이터들을 GPU 로 보냅니다... 
	g_transform.matWorld = m_matWorld;


	// 1. 상수버퍼를 가져온디..
	CConstBuffer* pBuffer = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM);
	pBuffer->SetData(&g_transform, sizeof(tTransform));
	pBuffer->UpdateData(); // 0번 레지스터에 저장한다. 



}