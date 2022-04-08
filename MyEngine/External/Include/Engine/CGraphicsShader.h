#pragma once
#include "CShader.h"

struct tScalarParamInfo
{
    wstring         strDesc;
    SCALAR_PARAM    eScalarParam;

};

struct tTexrParamInfo
{
    wstring         strDesc;
    TEX_PARAM       eTexParam;

};



class CGraphicsShader :
    public CShader
{

private:
    // 모든 Shader 들이 Layout 을 Static 으로 공유하고 있기 때문에
    // Shader 를 생성하는 모든 GRaphicsShader 들은 이 Layout 을 공유한다.
    // 따라서 외부에서 Layout 을 한번만 설정해주면 된다 .
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
    DS_TYPE                         m_eDSType;

    ComPtr<ID3D11InputLayout>       m_InputLayout;
    D3D11_PRIMITIVE_TOPOLOGY        m_eTopology; // Triangle? Rectangle? 

    vector<tScalarParamInfo>        m_vecScalarParamInfo;
    vector<tTexrParamInfo>          m_VecTexParamInfo;


  
public:

    int CreateVertexShader(const wstring& _strRrelativePath, const string& _strFunc);
    // int CreateHullShader(const wstring& _strRrelativePath, const string& _strVSFunc);
     //int CreateDomainShader(const wstring& _strRrelativePath, const string& _strVSFunc);
     //int CreateGeometryShader(const wstring& _strRrelativePath, const string& _strVSFunc);
    int CreatePixelShader(const wstring& _strRrelativePath, const string& _strFunc);


    void SetRSType(RS_TYPE _eType) { m_eRSType = _eType; }
    void SetDSType(DS_TYPE _eType) { m_eDSType = _eType; }

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _eTopology) { m_eTopology = _eTopology; }
    
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return m_eTopology; }


    virtual void UpdateData() override;

public:
    void AddScalarParamInfo(const wstring& _strDesc, SCALAR_PARAM _eParamType);
    void AddtexParamInfo(const wstring& _strDesc, TEX_PARAM _eParamType);
   
    const vector<tScalarParamInfo>& GetScalarParamInfo() { return m_vecScalarParamInfo; }
    const vector<tTexrParamInfo>& GetTexParamInfo() { return m_VecTexParamInfo; }



public:
    CGraphicsShader();
    ~CGraphicsShader();




};

