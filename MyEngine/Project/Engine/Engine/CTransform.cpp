#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"


CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
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


	// ȸ���� : radian 
	Matrix matRotX = XMMatrixRotationX(m_vRelativeRot.x);
	Matrix matRotY = XMMatrixRotationY(m_vRelativeRot.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRelativeRot.z); 
	Matrix matRotation = matRotX * matRotY * matRotZ;

	// World Matrix ���� 
	m_matWorld = matScale * matRotation * matTranlation; // [ S * R * T ]



}



void CTransform::UpdateData()
{
	// �ʿ��� �����͵��� GPU �� �����ϴ�... 
	g_transform.matWorld = m_matWorld;


	// 1. ������۸� �����µ�..
	CConstBuffer* pBuffer = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM);
	pBuffer->SetData(&g_transform, sizeof(tTransform));
	pBuffer->UpdateData(); // 0�� �������Ϳ� �����Ѵ�. 



}