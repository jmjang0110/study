#include "pch.h"
#include "CPlayerScript.h"

#include "CTransform.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CPlayerScript::CPlayerScript()
	: m_fSpeed(0.5f)
{
}

CPlayerScript::~CPlayerScript()
{
}


void CPlayerScript::start()
	
{
	Vec3 vPos = Vec3(0.f, 0.f, 0.5f); //Z : 0.5f 만큼 이동 
	Transform()->SetPos(vPos);
}

void CPlayerScript::update()
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

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRotation();
		vRot.y += DT * XM_2PI;
		Transform()->SetRotation(vRot);
	}


}

void CPlayerScript::lateupdate()
{
}

