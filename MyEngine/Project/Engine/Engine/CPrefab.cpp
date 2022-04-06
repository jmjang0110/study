#include "pch.h"
#include "CPrefab.h"
#include "CGameObject.h"



CPrefab::CPrefab()
	: m_pProtoObj(nullptr)
{
}

// ���� ������Ʈ�� ��� 
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
	// ���� ��ü ���纻�� �ѱ��. 
	return m_pProtoObj->Clone();

}