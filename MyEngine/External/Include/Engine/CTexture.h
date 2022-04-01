#pragma once
#include "CRes.h"

#include <DirectXTex\DirectXTex.h>


#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex/DirectXTex")
#endif


/*
    ScratchImage �� �Լ��� ���ؼ� Pixel data ���� 
    ���� �Ҵ� �Ǿ Heap �޸𸮿� ����Ǿ��ְ� 
    ScratchImages�� �� �ּҸ� ����Ű�� �����̴� .

    �츮�� ScratchImage �� ���ؼ� �޸𸮿� ����Ǿ��ִ�
    PixelData ���� ���� �� �� �ִ� .

    ScratchImage                        m_Image;    // ���Ϸκ��� �ε��� �ؽ��� �������� �ý��� �޸� ����
    ComPtr<ID3D11Texture2D>             m_pTex2D;   // GPU �� �ε��� �ؽ��� �����͸� �����ϴ� �������̽�    
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;     // Texture2D �� ShaderResource �뵵�� �����ϴ� �߰� �Ű�ü 

*/
class CTexture :
    public CRes
{
private:
   
    ScratchImage                    m_Image; // DirectXTex���� �������ִ� Ŭ���� / [ ScratchImage ] : ���Ϸ� ���� �ε��� �ؽ��� �������� �ý��� �޸� ����
    ComPtr<ID3D11Texture2D>         m_pTex2D;// ScratImage �� GPU �޸𸮷� �Ű��� �� Texture ������ ����Ű�� ������
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

