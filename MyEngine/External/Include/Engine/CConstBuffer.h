#pragma once
#include "CEntity.h"
#include "CKeyMgr.h"
#include "CKeyMgr.h"
#include "CKeyMgr.h"
class CConstBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer>    m_CB;
    D3D11_BUFFER_DESC       m_Desc;

    CB_TYPE                 m_eCBType; // 상수버퍼를 바인딩 할 레지스터 번호 
    
public:
    virtual void UpdateData() override;
    int Create(UINT _iBufferSize);


    void SetData(void* _pData, UINT _iSize);

    virtual CConstBuffer* Clone() { return nullptr; }


public:
    CConstBuffer(CB_TYPE _eType); // Type 을 전달해야 만들어지게끔 ( 자신의 고유한 레지스터 번호 ) 
    ~CConstBuffer();


};

