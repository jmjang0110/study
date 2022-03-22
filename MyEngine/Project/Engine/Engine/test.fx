#ifndef _TEST
#define _TEST

// Vertex Shader 
// �Է����� ������ ���´�.
// float3 : Vec3 
struct VTX_IN
{
    float3 vPos : POSITION; // semantic
    floar4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f; // ����ü �ʱ�ȭ = {}; (C++) 
        
    output.vPosition = float4(_in.vPos, 1.f);
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