#include "ContentTransform.fx"
#include "ContentAnimation.fx"
#include "ContentLight.fx"
#include "ContentRenderBaseValue.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 WORLDPOSITION : POSITION2;
    float4 WVPPOSITION : POSITION5;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
};



Output ContentMeshDeferred_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    NewOutPut.WVPPOSITION = NewOutPut.POSITION;
    
    NewOutPut.WORLDPOSITION = mul(InputPos, WorldMatrix);
    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    NewOutPut.NORMAL = mul(InputNormal, WorldView);
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);

SamplerState ENGINEBASE : register(s0);

struct DeferredOutPut
{
    float4 DifTarget  : SV_Target1;
    float4 PosTarget  : SV_Target2;
    float4 NorTarget  : SV_Target3;
};

cbuffer ClipData : register(b6)
{
    float2 MinClipData;
    float2 MaxClipData;
};

cbuffer WaterHeight : register(b4)
{
    float4 WaterHeight;
};

cbuffer IsOn : register(b7)
{
    bool isGamma;
    bool isHDR;
    bool2 padding;
};

DeferredOutPut ContentMeshDeferred_PS(Output _Input)
{
    if (_Input.WORLDPOSITION.y < WaterHeight.x)
    {
        clip(-1);
    }
    
    DeferredOutPut NewOutPut = (DeferredOutPut) 0;
    
    if (saturate(_Input.TEXCOORD.x) < MinClipData.x && saturate(_Input.TEXCOORD.y) < MinClipData.y)
    {
        clip(-1);
    }
        
    if (saturate(_Input.TEXCOORD.x) > MaxClipData.x && saturate(_Input.TEXCOORD.y) > MaxClipData.y)
    {
        clip(-1);
    }
    
    //UV°ª º¯°æ
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
        
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    if (isGamma == true)
    {
        Color = pow(Color, 2.2f);
    }
    
    Color *= MulColor;
    Color += AddColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
     //Fade
    float4 FadeMask = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);

    if (Delta > 0.0f && FadeMask.r <= Delta)
    {
        clip(-1);
    }
    
    if (FadeMask.r > Delta && FadeMask.r <= Delta * 1.25f)
    {
        Color = float4(FadeColor.r, FadeColor.g, FadeColor.b, 1.0f);
    }
    
    NewOutPut.DifTarget = Color;
    NewOutPut.PosTarget = _Input.VIEWPOSITION;
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    
    return NewOutPut;
}

