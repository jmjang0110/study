#pragma once
#include "CRes.h"
#include "CGraphicsShader.h"

class CGraphicsShader;


class CMaterial :
    public CRes
{

private:
    tScalarParam              m_Param;
    Ptr<CGraphicsShader>   m_pShader;

    vector<tParamInfo > m_vecParamInfo;
public:
    void SetShader(Ptr<CGraphicsShader>  _pShader);
    Ptr<CGraphicsShader>  GetShader() { return m_pShader; }

    void SetScalarParam(SCALAR_PARAM _eType, void* _pData );
    void SetScalarParam(const wstring& _strParamName, void* _pData);


    void UpdateData();


public:
    virtual int Load(const wstring& _strFilePath) override { return S_OK; }



public:
    CMaterial();
    ~CMaterial();

};

