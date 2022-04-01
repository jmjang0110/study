#pragma once
#include "CRes.h"

#include <DirectXTex\DirectXTex.h>


#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex/DirectXTex")
#endif


/*
    ScratchImage 는 함수를 통해서 Pixel data 들이 
    동적 할당 되어서 Heap 메모리에 저장되어있고 
    ScratchImages는 그 주소를 가리키는 구조이다 .

    우리는 ScratchImage 를 통해서 메모리에 저장되어있는
    PixelData 들을 접근 할 수 있다 .

    ScratchImage                        m_Image;    // 파일로부터 로딩한 텍스쳐 데이터의 시스템 메모리 관리
    ComPtr<ID3D11Texture2D>             m_pTex2D;   // GPU 에 로딩된 텍스쳐 데이터를 관리하는 인터페이스    
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;     // Texture2D 를 ShaderResource 용도로 전달하는 중간 매개체 

*/
class CTexture :
    public CRes
{
private:
   
    ScratchImage                    m_Image; // DirectXTex에서 지원해주는 클래스 / [ ScratchImage ] : 파일로 부터 로딩한 텍스쳐 데이터의 시스템 메모리 관리
    ComPtr<ID3D11Texture2D>         m_pTex2D;// ScratImage 를 GPU 메모리로 옮겼을 때 Texture 데이터 가리키는 포인터
    ComPtr<ID3D11ShaderResourceView> m_pSRV;



protected:
    virtual int Load(const wstring& _strFilePath);

public:
    // PIPELINE_STAGE
    void UpdateData(int _PipelineStage ,int _iRegisterNum);

public:
    CTexture();
    ~CTexture();

};

