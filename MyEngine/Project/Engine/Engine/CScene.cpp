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
