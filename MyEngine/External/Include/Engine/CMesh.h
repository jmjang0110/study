#pragma once
#include "CRes.h"
class CMesh :
    public CRes
{
private:
    
    ComPtr<ID3D11Buffer>    m_VB; // Vertex Buffer 
    ComPtr<ID3D11Buffer>    m_IB; // Index Buffer 

    D3D11_BUFFER_DESC       m_tVBDesc;
    D3D11_BUFFER_DESC       m_tIBDesc;


    UINT                    m_iVtxCount;
    UINT                    m_iIdxCount;

    void*                   m_pVtxSys; // GPU ���� CPU�޸��� �ý��� �޸��� ���� ������ �����Ѵ�. 
    void*                   m_pIdxSys;


public:
    virtual int Load(const wstring& _strFilePath) { return S_OK; }
    virtual void UpdateData() override;

    
    // ���� ��ŭ �о GPU �� �������ϴ� ? 
    int Create(void* _pVtxSys,UINT _iVtxCount, void* _pIdxSys, UINT _iIdxCount);
    
    void render();

public:
    CMesh();
    ~CMesh();


};

