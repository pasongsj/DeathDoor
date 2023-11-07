#include "ContentTransform.fx"
#include "ContentRenderBaseValue.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

Output ContentMeshTexture_VS(Input _Input)
{
    
    Output NewOutPut = (Output) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    
    return NewOutPut;
}

SamplerState ENGINEBASE : register(s0);

float4 ContentMeshTexture_PS(Output _Input) : SV_Target6
{
    //UV°ª º¯°æ
    
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

