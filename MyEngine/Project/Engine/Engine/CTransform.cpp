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

	// Transform 행렬 만들기
	m_matWorld._11 = m_vRelativeScale.x; m_matWorld._12 = 0;				  m_matWorld._13 = 0.f;				   m_matWorld._14 = 0.f;
	m_matWorld._21 = 0;					 m_matWorld._22 = m_vRelativeScale.y; m_matWorld._23 = 0.f;				   m_matWorld._24 = 0.f;
	m_matWorld._31 = 0;					 m_matWorld._32 = 0;				  m_matWorld._33 = m_vRelativeScale.z; m_matWorld._34 = 0.f;
	m_matWorld._41 = m_vRelativePos.x;	 m_matWorld._42 = m_vRelativePos.y;   m_matWorld._43 = m_vRelativePos.z;   m_matWorld._44 = 1.f;
}



void CTransform::UpdateData()
{
	// 필요한 데이터들을 GPU 로 보냅니다... 

	// 1. 상수버퍼를 가져온디..
	CConstBuffer* pBuffer = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM);
	pBuffer->SetData(&m_matWorld, sizeof(Matrix));
	pBuffer->UpdateData(); // 0번 레지스터에 저장한다. 



}