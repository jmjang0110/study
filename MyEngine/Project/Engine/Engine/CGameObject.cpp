#include "pch.h"
#include "CGameObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CComponent.h"
#include "CTransform.h"
#include "CMeshRender.h"



CGameObject::CGameObject()
	: m_arrCom{}
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Arr(m_arrCom);

}

void CGameObject::update()
{
	if (KEY_PRESSED(KEY::LEFT))
	{
		Vec3 vPos = Transform()->GetPos();
		vPos.x -= DT * 0.5f;
		Transform()->SetPos(vPos);


	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		Vec3 vPos = Transform()->GetPos();
		vPos.x += DT * 0.5f;
		Transform()->SetPos(vPos);
  
	}


	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->update();

	}
}

void CGameObject::lateupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->lateupdate();

	}
}

void CGameObject::finalupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finalupdate();

	}
}

void CGameObject::render()
{
	if (nullptr != MeshRender()) // MeshRender 기능을 보유하고 있다면 
		MeshRender()->render();
	
}

void CGameObject::AddComponent(CComponent* _component)
{
	COMPONENT_TYPE eType = _component->GetType();

	assert(nullptr == m_arrCom[(UINT)eType]);

	m_arrCom[(UINT)eType] = _component;
	_component->m_pOwner = this;

}


