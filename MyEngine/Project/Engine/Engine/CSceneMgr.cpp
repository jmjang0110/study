#include "pch.h"
#include "CSceneMgr.h"


#include "CDevice.h"
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"



#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CScene.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"
#include "CCameraMoveScript.h"
#include "CCamera.h"
#include "CMaterial.h"


#include "CTexture.h"
#include "CMissileScript.h"
#include "CTransform.h"
#include "CPrefab.h"





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

	//  ** Layer 세팅 
	m_pCurScene->SetLayerName(0, L"Default");
	m_pCurScene->SetLayerName(1, L"Player");
	m_pCurScene->SetLayerName(2, L"Monster");
	
	// ** teture 한장 로딩해보기 
	CResMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Player.bmp");
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"PlayerTexture");


	// ** Prefab 
		// 오브젝트 생성 
	CGameObject* pMissileObj = new CGameObject;
	pMissileObj->AddComponent(new CTransform);
	pMissileObj->AddComponent(new CMeshRender);
	pMissileObj->AddComponent(new CMissileScript);

	pMissileObj->Transform()->SetScale(Vec3(50.f, 50.f, 1.f));
	pMissileObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
	pMissileObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TestMtrl"));

	CResMgr::GetInst()->AddRes<CPrefab>(L"MissilePrefab", new CPrefab(pMissileObj));


	//  텍스쳐를 렌더링 파이프라인 PixelShader 단계 때 t0 레지스터에 바인딩 시켜 둠 
	// pTex->UpdateData((int)PIPELINE_STAGE::PS, 0);

	//  **  Scene 에 Camera Object 추가 
	CGameObject* pCamObj = new CGameObject;
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	m_pCurScene->AddObject(pCamObj, L"Default");



	// ** Scene 에 GameObject 추가
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetScale(Vec3(200.f, 200.f, 1.f));

	
	//pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
	pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TestMtrl"));

	int a = 1;
	//pObject->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, &a);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(L"IsColorRed", &a);
	pObject->MeshRender()->GetMaterial()->SetTexParam(L"OutputTex", pTex);


	m_pCurScene->AddObject(pObject, L"Default");


	// ** 오브젝트 복사본 생성 
	pObject = pObject->Clone();
	pObject->SetName(L"Player_Clone");
	pObject->Transform()->SetPos(pObject->Transform()->GetPos() + Vec3(200.f, 0.f, 0.f));
	m_pCurScene->AddObject(pObject, L"Default");




	m_pCurScene->start();
}

void CSceneMgr::progress()
{
	m_pCurScene->update();
	m_pCurScene->lateupdate();
	m_pCurScene->finalupdate();
}

void CSceneMgr::render()
{
	CDevice::GetInst()->ClearTarget();

	m_pCurScene->render();

	CDevice::GetInst()->Present();
}


void CSceneMgr::SpawnObject(CGameObject* _pSpawnObject, Vec3 _vWorldPos, wstring _strName, UINT _iLayerIdx)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::CREATE_OBJ;
	info.lParam = (DWORD_PTR)_pSpawnObject;
	info.wParam = (DWORD_PTR)_iLayerIdx;

	_pSpawnObject->Transform()->SetPos(_vWorldPos);
	_pSpawnObject->SetName(_strName);

	CEventMgr::GetInst()->AddEvent(info);


}

void CSceneMgr::SpawnObject(CGameObject* _pSpawnObject, UINT _iLayerIdx)
{

	tEventInfo info = {};
	info.eType = EVENT_TYPE::CREATE_OBJ;
	info.lParam = (DWORD_PTR)_pSpawnObject;
	info.wParam = (DWORD_PTR)_iLayerIdx;

	CEventMgr::GetInst()->AddEvent(info);



}

