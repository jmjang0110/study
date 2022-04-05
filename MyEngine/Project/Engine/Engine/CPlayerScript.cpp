#include "pch.h"
#include "CPlayerScript.h"


#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CTransform.h"
#include "CMeshRender.h"
#include "CMissileScript.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CResMgr.h"


CPlayerScript::CPlayerScript()
	: m_fSpeed(0.5f)
{
}

CPlayerScript::~CPlayerScript()
{
}


void CPlayerScript::start()
	
{
	//Vec3 vPos = Vec3(0.f, 0.f, 0.5f); //Z : 0.5f 만큼 이동 
	//Transform()->SetPos(vPos);
}

void CPlayerScript::update()
{
	if (KEY_PRESSED(KEY::LEFT))
	{
		Vec3 vPos = Transform()->GetPos();
		vPos.x -= DT * 0.5f; // 1초 눌러야 0.5 픽셀 이동 
		Transform()->SetPos(vPos);


	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		Vec3 vPos = Transform()->GetPos();
		vPos.x += DT * 0.5f;
		Transform()->SetPos(vPos);

	}

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRotation();
		vRot.y += DT * XM_2PI;
		Transform()->SetRotation(vRot);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		// 오브젝트 생성 
		CGameObject* pMissileObj = new CGameObject;
		pMissileObj->AddComponent(new CTransform);
		pMissileObj->AddComponent(new CMeshRender);
		pMissileObj->AddComponent(new CMissileScript);

		pMissileObj->Transform()->SetPos(Transform()->GetPos() + Vec3(0.f, 50.f, 0.f));
		pMissileObj->Transform()->SetScale(Vec3(50.f, 50.f, 1.f));
		pMissileObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
		pMissileObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TestMtrl"));

		// 생성된 오브젝트 Scene에 추가 
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
		pCurScene->AddObject(pMissileObj, 0);
	}

}

void CPlayerScript::lateupdate()
{
}

