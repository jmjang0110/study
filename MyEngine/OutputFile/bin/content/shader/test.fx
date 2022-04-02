#ifndef _TEST
#define _TEST

// 0 번 슬롯으로 전달한다고 했었다. 
cbuffer TRANSFORM : register(b0)
{
    // 행 우선으로 읽기
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    
}

cbuffer SCALARL_PARAM : register(b1)
{
    // 4byte 짜리 배열을 만들 수 없기 때문에 이렇게 일일히 쓴다 .
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    matrix g_mat_0;
    matrix g_mat_1;
    matrix g_mat_2;
    matrix g_mat_3;
    
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);

Texture2D g_texcube_0 : register(t4);
Texture2D g_texcube_1 : register(t5);

Texture2D g_texarr_0 : register(t6);
Texture2D g_texarr_1 : register(t7);




SamplerState g_sam_0 : register(s0);    // Anisotropic Filter 
SamplerState g_sam_1 : register(s1);    // Point Filter 



// StructuredBuffer<float4> g_buffer : register(t1);
// sampler g_sam : register(s0);
// RWStructuredBuffer<float4> g_rwbuffer : register(u0);


//==============
// Vertex Shader 
//==============


// 입력으로 정점이 들어온다.
// float3 : Vec3 
struct VTX_IN
{
    float3 vPos     : POSITION; // semantic
    float4 vColor   : COLOR;
    float2 vUV      : TEXCOORD;
};

struct VTX_OUT 
{
    float4 vPosition    : SV_Position;
    float4 vColor       : COLOR;
    float2 vUV          : TEXCOORD;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f; // 구조체 초기화 = {}; (C++) 
        
    
    float4 vWorldPos = mul(float4(_in.vPos,1.f), g_matWorld);   // World Space
    float4 vViewPos = mul(vWorldPos, g_matView);                // Camera Space  
    float4 vProjPos = mul(vViewPos, g_matProj);                 // Projection Space 
    
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
   
    
    return output;
}



//==============
// Pixel Shader 
//==============

// Rasterizer 단계로 간다. 
// 정점이 만드는 도형 (Topology ) 안에 들어오는 픽셀을 검출 ( 픽쉘 세이더 후보 )
// 해당 픽셀들 마다 픽셀 쉐이더 호출 
// --> Pixel Shader

// Pixel Shader 는 Vertex Shader 에서 반환한 VTX_OUT 값이 인자로 들어온다. 
float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;

     //vOutColor = _in.vColor;
    
    //if (g_int_0)
    //    vOutColor = float4(1.f, 0.f, 0.f, 1.f);
    //else
    //    vOutColor = float4(0.f, 0.f, 1.f, 1.f);
        
    vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    
    return vOutColor;
    
}
#endif
