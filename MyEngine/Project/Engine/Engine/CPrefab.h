#pragma once
#include "CRes.h"

class CGameObject;

/*
    필요한 리소스들을 게임이 시작되기 전에 미리 로드해서
    복제본을 넘겨준다. 

*/
class CPrefab :
    public CRes
{

private:
    CGameObject* m_pProtoObj;



public:
    CGameObject* Instantiate();

    virtual int Load(const wstring& _strFilePath) { return S_OK; }

public:

    CPrefab();
    CPrefab(CGameObject* _pProtoObj);
    ~CPrefab();

};

