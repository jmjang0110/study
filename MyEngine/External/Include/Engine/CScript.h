#pragma once
#include "CComponent.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CLayer.h"



class CScript :
    public CComponent
{

private:
    const int m_iScriptID; // 스크립트 구별용도 ( 스크립트 타입 )

public:
    virtual void start() {};
    virtual void update() {};
    virtual void lateupdate() {};
    virtual void finalupdate() final{}; // final : 더이상 자식에게 파생시키지 않는다. 
                                        // 이 밑으로 더이상 가상함수를 구현할 수 없다. 
    // 이렇게 한 이유는 finalupdate : 이제 업데이트를 끝내자 인데 업데이트 다 하고 나서 
    // 스크립트로 finalupdate 를 또 해버리면 프레임이 꼬인다. 


    // 충돌이 발생하면 해당 Object 가 가지고 있는 Script 에서 처리한다. 
    virtual void OnCollisionEnter(CGameObject* _OtherObject) {};
    virtual void OnCollision(CGameObject* _OtherObject) {};
    virtual void OnCollisionExit(CGameObject* _OtherObject) {};




    virtual CScript* Clone() = 0;


public:
    CScript();
    ~CScript();


};

