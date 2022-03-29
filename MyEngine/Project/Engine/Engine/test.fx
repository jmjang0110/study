#ifndef _TEST
#define _TEST

// 0 번 슬롯으로 전달한다고 했었다. 
cbuffer TRANSFORM : register(b0)
{
    // 행 우선으로 읽기
    row_major matrix g_matWorld;
}

// Texture2D g_tex_0 : register(t0);
// StructuredBuffer<float4> g_buffer : register(t1);
// sampler g_sam : register(s0);
// RWStructuredBuffer<float4> g_rwbuffer : register(u0);



// Vertex Shader 
// 입력으로 정점이 들어온다.
// float3 : Vec3 
struct VTX_IN
{
    float3 vPos : POSITION; // semantic
    float4 vColor : COLOR;
};

struct VTX_OUT 
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f; // 구조체 초기화 = {}; (C++) 
        
    
    float4 vFinalPos = mul(float4(_in.vPos,1.f), g_matWorld);
     
    output.vPosition = vFinalPos;
    output.vColor = _in.vColor;
    
   
    
    return output;
}



// Rasterizer 단계로 간다. 
// 정점이 만드는 도형 (Topology ) 안에 들어오는 픽셀을 검출 ( 픽쉘 세이더 후보 )
// 해당 픽셀들 마다 픽셀 쉐이더 호출 
// --> Pixel Shader

// Pixel Shader 는 Vertex Shader 에서 반환한 VTX_OUT 값이 인자로 들어온다. 
float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = _in.vColor;
    
    return vOutColor;
    
}
#endif
