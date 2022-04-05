#pragma once
#include "CRes.h"

class CGameObject;

/*
    �ʿ��� ���ҽ����� ������ ���۵Ǳ� ���� �̸� �ε��ؼ�
    �������� �Ѱ��ش�. 

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

