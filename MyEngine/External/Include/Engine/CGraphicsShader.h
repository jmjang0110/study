#pragma once
#include "CShader.h"
class CGraphicsShader :
    public CShader
{

private:
    // ��� Shader ���� Layout �� Static ���� �����ϰ� �ֱ� ������
    // Shader �� �����ϴ� ��� GRaphicsShader ���� �� Layout �� �����Ѵ�.
    // ���� �ܺο��� Layout �� �ѹ��� �������ָ� �ȴ� .
    static vector<D3D11_INPUT_ELEMENT_DESC> g_vecLayout;
    static UINT g_iOffSet;

public:
    static void AddInputLayout(D3D11_INPUT_ELEMENT_DESC _desc);


private:
    // Compile - Fail Reason store / Code 
    ComPtr<ID3DBlob>                m_VSBlob; // Vertex Shader 
    ComPtr<ID3DBlob>                m_HSBlob; // Hull Shader 
    ComPtr<ID3DBlob>                m_DSBlob; // Domain Shader
    ComPtr<ID3DBlob>                m_GSBlob; // Geometry Shader
    ComPtr<ID3DBlob>                m_PSBlob; // Pixel Shader 

    ComPtr<ID3D11VertexShader>      m_VS;
    ComPtr<ID3D11HullShader>        m_HS;
    ComPtr<ID3D11DomainShader>      m_DS;
    ComPtr<ID3D11GeometryShader>    m_GS;
    ComPtr<ID3D11PixelShader>       m_PS;


    RS_TYPE                         m_eRSType;
    ComPtr<ID3D11InputLayout>       m_InputLayout;
    D3D11_PRIMITIVE_TOPOLOGY        m_eTopology; // Triangle? Rectangle? 

public:

    int CreateVertexShader(const wstring& _strRrelativePath, const string& _strFunc);
    // int CreateHullShader(const wstring& _strRrelativePath, const string& _strVSFunc);
     //int CreateDomainShader(const wstring& _strRrelativePath, const string& _strVSFunc);
     //int CreateGeometryShader(const wstring& _strRrelativePath, const string& _strVSFunc);
    int CreatePixelShader(const wstring& _strRrelativePath, const string& _strFunc);


    void SetRSType(RS_TYPE _eType) { m_eRSType = _eType; }
    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _eTopology) { m_eTopology = _eTopology; }
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return m_eTopology; }


    virtual void UpdateData() override;


public:
    CGraphicsShader();
    ~CGraphicsShader();




};

