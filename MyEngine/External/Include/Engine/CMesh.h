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

    void*                   m_pVtxSys; // GPU 말고 CPU메모리인 시스템 메모리의 정점 정보도 관리한다. 
    void*                   m_pIdxSys;


public:
    virtual int Load(const wstring& _strFilePath) { return S_OK; }
    virtual void UpdateData() override;

    
    // 내가 얼만큼 읽어서 GPU 로 보내야하니 ? 
    int Create(void* _pVtxSys,UINT _iVtxCount, void* _pIdxSys, UINT _iIdxCount);
    
    void render();

public:
    CMesh();
    ~CMesh();


};

