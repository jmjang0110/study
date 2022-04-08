#include "pch.h"
#include "CGameObject.h"


#include "CComponent.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CEventMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CLayer.h"

#include "CCollider2D.h"



CGameObject::CGameObject()
	: m_arrCom{}
	, m_pParent(nullptr)
	, m_bActive(true)
	, m_bDead(false)
	, m_iLayerIdx(-1)
{
}

CGameObject::CGameObject(const CGameObject& _origin)
	:CEntity(_origin)
	, m_arrCom{}
	, m_bActive(true)
	, m_bDead(false)
	, m_iLayerIdx(-1)
	, m_pParent(nullptr)

{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != _origin.m_arrCom[i])
			AddComponent(_origin.m_arrCom[i]->Clone());
	}
	for (size_t i = 0; i < _origin.m_vecChild.size(); ++i)
	{
		AddChild(_origin.m_vecChild[i]->Clone());

	}

}

CGameObject::~CGameObject()
{
	Safe_Del_Arr(m_arrCom);
	Safe_Del_Vec(m_vecChild);

}

void CGameObject::start()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->start();

	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->start();

	}


}

void CGameObject::update()
{
	


	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->update();

	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->update();

	}
}

void CGameObject::lateupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->lateupdate();

	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->lateupdate();

	}

}

void CGameObject::finalupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finalupdate();

	}


	// Layer 에 등록 
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(m_iLayerIdx);
	pLayer->RegisterObject(this);


	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finalupdate();

	}

	


}

void CGameObject::render()
{
	if (nullptr != MeshRender()) // MeshRender 기능을 보유하고 있다면 
		MeshRender()->render();
	
	if (nullptr != Collider2D())
		Collider2D()->render();

}

void CGameObject::AddChild(CGameObject* _pChild)
{
	int iLayerIdx = _pChild->m_iLayerIdx;

	// 자식으로 들오오는 오브젝트가 루트 오브젝트 이고 , 특정 레이어 소속이라면 
	if (nullptr == _pChild->GetParent() && -1 != iLayerIdx)
	{
		// 레이어 에서 루트 오브젝트로서 등록 해제 
		_pChild->Deregister();
		_pChild->m_iLayerIdx = iLayerIdx;

	}

	// 다른 부모 오브젝트가 이미 있다면
	if (_pChild->GetParent())
	{
		_pChild->DisconnectBetweenParent();

	}


	//_pChild->m_iLayerIdx = iLayerIdx;
	m_vecChild.push_back(_pChild);
	_pChild->m_pParent = this;


}

void CGameObject::AddComponent(CComponent* _component)
{
	COMPONENT_TYPE eType = _component->GetType();

	assert(nullptr == m_arrCom[(UINT)eType]);

	m_arrCom[(UINT)eType] = _component;
	_component->m_pOwner = this;

}

// 소속되어있는 Layer 로 부터 Object 객체관계를 끊는다. 
void CGameObject::Deregister()
{
	if (-1 == m_iLayerIdx)
	{
		return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pCurLayer = pCurScene->GetLayer(m_iLayerIdx);
	pCurLayer->DeregisterObject(this);

}

void CGameObject::DisconnectBetweenParent()
{
	assert(m_pParent); // 부모가 있는가 
	
	vector<CGameObject*>::iterator iter = m_pParent->m_vecChild.begin();

	for (; iter != m_pParent->m_vecChild.end(); ++iter)
	{
		// 나를 Child 로 여기는 부모와 연결을 끊는다. 
		if ((*iter) == this)
		{
			m_pParent->m_vecChild.erase(iter);

		}

	}

	m_pParent = nullptr;

}

void CGameObject::Destroy()
{
	if (m_bDead)
		return;

	tEventInfo info = {};


	info.eType = EVENT_TYPE::DELETE_OBJ;
	info.lParam = (DWORD_PTR)this;

	CEventMgr::GetInst()->AddEvent(info);


}


