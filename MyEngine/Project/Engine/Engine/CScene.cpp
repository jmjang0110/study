#include "pch.h"
#include "CScene.h"
#include "CLayer.h"
#include "CGameObject.h"



CScene::CScene()
	: m_arrLayer{}
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i] = new CLayer;
	}

}

CScene::~CScene()
{
	Safe_Del_Arr(m_arrLayer);

}


void CScene::start()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->start();

	}

}

void CScene::update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->update();

	}


}

void CScene::lateupdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->lateupdate();

	}


}

void CScene::finalupdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->finalupdate();

	}


}

void CScene::render()
{
	// 렌더링 
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->render();

	}

	// 지운다. 
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Clear();

	}
}

void CScene::SetLayerName(int _iLayerIdx, const wstring& _strName)
{
	assert(0 <= _iLayerIdx && _iLayerIdx < MAX_LAYER);
	m_arrLayer[_iLayerIdx]->SetName(_strName);


}


int CScene::GetLayerIdxFromName(const wstring& _strName)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (m_arrLayer[i]->GetName() == _strName)
		{
			return i;
		}
	}

	return -1;


}

// LayerName Layer에 Obj 추가 - 최상위 오브젝트 단위로 추가된다. 
void CScene::AddObject(CGameObject* _pRootObj, const wstring& _strLayerName)
{
	int iLayerIdx = GetLayerIdxFromName(_strLayerName);

	assert(iLayerIdx != -1);
	// CScene 에서는 최상위 오브젝트만 다루기 때문에 
	// 부모가 있는 오브젝트 들이 들어가면 안된다. 
	assert(!_pRootObj->m_pParent);

	AddObject(_pRootObj, iLayerIdx);

}


// LayerIdx Layer에 Obj 추기 - 최상위 오브젝트 단위로 추가된다. 
void CScene::AddObject(CGameObject* _pRootObj, int _iLayerIdx)
{
	assert(0 <= _iLayerIdx && _iLayerIdx < MAX_LAYER);
	assert(!_pRootObj->m_pParent);

	m_arrLayer[_iLayerIdx]->AddObject(_pRootObj);

	// 자기 오브젝트 들도 해당 레이어의 인덱스를 알려준다. 
	list<CGameObject*> queue;
	queue.push_back(_pRootObj);

	while (!queue.empty())
	{
		CGameObject* pTargetObj = queue.front();
		queue.pop_front();

		if (-1 == pTargetObj->m_iLayerIdx)
			pTargetObj->m_iLayerIdx = _iLayerIdx;

		pTargetObj->m_iLayerIdx = _iLayerIdx;
		const vector<CGameObject*>& vecChild = pTargetObj->GetChild();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);

		}
	}

	_pRootObj->m_iLayerIdx = _iLayerIdx;

}



