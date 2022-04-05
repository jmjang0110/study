#include "pch.h"
#include "CScene.h"
#include "CLayer.h"



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

// LayerName Layer에 Obj 추가
void CScene::AddObject(CGameObject* _pObj, const wstring& _strLayerName)
{
	int iLayerIdx = GetLayerIdxFromName(_strLayerName);
	assert(iLayerIdx != -1);

	AddObject(_pObj, iLayerIdx);

}


// LayerIdx Layer에 Obj 추기 
void CScene::AddObject(CGameObject* _pObj, int _iLayerIdx)
{
	assert(0 <= _iLayerIdx && _iLayerIdx < MAX_LAYER);
	m_arrLayer[_iLayerIdx]->AddObject(_pObj);


}



