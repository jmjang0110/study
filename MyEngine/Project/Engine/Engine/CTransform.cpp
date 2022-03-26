#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"


CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{

}

CTransform::~CTransform()
{

}

void CTransform::UpdateData()
{
	// 필요한 데이터들을 GPU 로 보냅니다... 

	// 1. 상수버퍼를 가져온디..
	CConstBuffer* pBuffer = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM); 
	pBuffer->SetData(&m_vRelativePos, sizeof(Vec4));
	pBuffer->UpdateData(); // 0번 레지스터에 저장한다. 



}

void CTransform::finalupdate()
{
}



