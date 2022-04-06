#include "pch.h"
#include "CPrefab.h"
#include "CGameObject.h"



CPrefab::CPrefab()
	: m_pProtoObj(nullptr)
{
}

// 원형 오브젝트로 등록 
CPrefab::CPrefab(CGameObject* _pProtoObj)
	: m_pProtoObj(_pProtoObj)
{

}

CPrefab::~CPrefab()
{
	SAFE_DELETE(m_pProtoObj);

}

// Return m_pProtoObj Clone();
CGameObject* CPrefab::Instantiate()
{
	// 원본 객체 복사본을 넘긴다. 
	return m_pProtoObj->Clone();

}