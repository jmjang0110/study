#include "pch.h"
#include "CPlayerScript.h"

#include "CTransform.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayerScript::start()
{
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

}

void CPlayerScript::lateupdate()
{
}

CPlayerScript::CPlayerScript()
{
}

CPlayerScript::~CPlayerScript()
{
}
