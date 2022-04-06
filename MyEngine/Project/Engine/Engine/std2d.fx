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

VTX_OUT VS_Std2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = nul(float4(_in.vPos, 1.f), g_matWVP);
    
    return output;
    
   
}


float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    
}


#endif
