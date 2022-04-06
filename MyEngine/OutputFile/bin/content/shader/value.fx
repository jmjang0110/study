#ifndef _VALUE
#define _VALUE

// ���� �������� ���� 


// 0 �� �������� �����Ѵٰ� �߾���. 
cbuffer TRANSFORM : register(b0)
{
    // �� �켱���� �б�
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
}

cbuffer SCALARL_PARAM : register(b1)
{
    // 4byte ¥�� �迭�� ���� �� ���� ������ �̷��� ������ ���� .
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




SamplerState g_sam_0 : register(s0); // Anisotropic Filter 
SamplerState g_sam_1 : register(s1); // Point Filter 



#endif
