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
    
    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    NewOutPut.NORMAL = mul(InputNormal, WorldView);
    
    return NewOutPut;
}

cbuffer ClipData : register(b0)
{
    float ClipData;
    float3 Padding;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);

SamplerState ENGINEBASE : register(s0);

struct DeferredOutPut
{
    float4 DifTarget : SV_Target1;
    float4 PosTarget : SV_Target2;
    float4 NorTarget : SV_Target3;
    float4 BlurTarget : SV_Target7;
};

DeferredOutPut ContentMeshDeferred_PS(Output _Input)
{
    DeferredOutPut NewOutPut = (DeferredOutPut) 0;
        
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    float4 MaskColor = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    if (MaskColor.r <= ClipData.x)
    {
        clip(-1);
    }
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    float4 BlurColor = float4(0.99f, 0.1f, 0.2f, Color.a);
    BlurColor.rgb = BlurColor.rgb * 0.5f;
    
    NewOutPut.DifTarget = BlurColor;
    NewOutPut.PosTarget = _Input.VIEWPOSITION;
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    NewOutPut.BlurTarget = BlurColor;
    
    return NewOutPut;
}

