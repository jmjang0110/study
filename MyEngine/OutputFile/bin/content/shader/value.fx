#ifndef _VALUE
#define _VALUE

// 공용 레지스터 선언 


// 0 번 슬롯으로 전달한다고 했었다. 
cbuffer TRANSFORM : register(b0)
{
    // 행 우선으로 읽기
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
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




SamplerState g_sam_0 : register(s0); // Anisotropic Filter 
SamplerState g_sam_1 : register(s1); // Point Filter 



#endif
