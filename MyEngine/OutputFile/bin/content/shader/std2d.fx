#ifndef _STD2D
#define _STD2D

#include "value.fx"


struct VTX_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};


// ============
// Std2D Shader
// ============
VTX_OUT VS_Std2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    return vOutColor;

}


// =================
// Collider2D Shader
// =================
VTX_OUT VS_Collider2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Collider2D(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
       
    vOutColor = float4(0.f, 1.f, 0.f, 1.f);
    
    if (0.1f <= _in.vUV.x && _in.vUV.x <= 0.9f
        && 0.1f <= _in.vUV.y && _in.vUV.y <= 0.9f)
    {
        discard;
    }
    
    //discard;
    //clip(-1);
    
    return vOutColor;
}







#endif
