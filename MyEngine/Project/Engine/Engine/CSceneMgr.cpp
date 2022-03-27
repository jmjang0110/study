#include "pch.h"
#include "CSceneMgr.h"

#include "CScene.h"


CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);

}


void CSceneMgr::init()
{
	m_pCurScene = new CScene;


}

void CSceneMgr::progress()
{
	m_pCurScene->update();
	m_pCurScene->lateupdate();
	m_pCurScene->finalupdate();

}

void CSceneMgr::render()
{
	m_pCurScene->render();


}
