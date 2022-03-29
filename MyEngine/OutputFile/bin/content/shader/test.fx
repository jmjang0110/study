#ifndef _TEST
#define _TEST

// 0 �� �������� �����Ѵٰ� �߾���. 
cbuffer TRANSFORM : register(b0)
{
    // �� �켱���� �б�
    row_major matrix g_matWorld;
}

// Texture2D g_tex_0 : register(t0);
// StructuredBuffer<float4> g_buffer : register(t1);
// sampler g_sam : register(s0);
// RWStructuredBuffer<float4> g_rwbuffer : register(u0);



// Vertex Shader 
// �Է����� ������ ���´�.
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
    VTX_OUT output = (VTX_OUT) 0.f; // ����ü �ʱ�ȭ = {}; (C++) 
        
    
    float4 vFinalPos = mul(float4(_in.vPos,1.f), g_matWorld);
     
    output.vPosition = vFinalPos;
    output.vColor = _in.vColor;
    
   
    
    return output;
}



// Rasterizer �ܰ�� ����. 
// ������ ����� ���� (Topology ) �ȿ� ������ �ȼ��� ���� ( �Ƚ� ���̴� �ĺ� )
// �ش� �ȼ��� ���� �ȼ� ���̴� ȣ�� 
// --> Pixel Shader

// Pixel Shader �� Vertex Shader ���� ��ȯ�� VTX_OUT ���� ���ڷ� ���´�. 
float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = _in.vColor;
    
    return vOutColor;
    
}
#endif
