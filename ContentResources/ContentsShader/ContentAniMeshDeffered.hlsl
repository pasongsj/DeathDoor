#include "ContentTransform.fx"
#include "ContentAnimation.fx"
#include "ContentLight.fx"
#include "ContentRenderBaseValue.fx"

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

Output ContentAniMeshDeferred_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    if (IsAnimation != 0)
    {
        Skinning(InputPos, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
        InputPos.w = 1.0f;
        InputNormal.w = 0.0f;
    }
    
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    NewOutPut.WVPPOSITION = NewOutPut.POSITION;
    
    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    _Input.NORMAL.w = 0.0f;
    NewOutPut.NORMAL = mul(InputNormal, WorldView);
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);
SamplerState ENGINEBASE : register(s0);

struct DeferredOutPut
{
    float4 DifTarget : SV_Target1;
    float4 PosTarget : SV_Target2;
    float4 NorTarget : SV_Target3;
};

cbuffer MaskInfo : register(b0)
{
    float UV_MaskingValue;
    float3 MaskingColor;
};

DeferredOutPut ContentAniMeshDeferred_PS(Output _Input)
{
    DeferredOutPut NewOutPut = (DeferredOutPut) 0;
    
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    float4 MaskColor;
    
    if (_Input.TEXCOORD.x <= UV_MaskingValue && _Input.TEXCOORD.y <= UV_MaskingValue)
    {
        MaskColor = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
        if (MaskColor.a > 0.0f)
        {
            Color.r = lerp(Color.r, MaskingColor.r, 0.9f);
            Color.g = lerp(Color.g, MaskingColor.g, 0.9f);
            Color.b = lerp(Color.b, MaskingColor.b, 0.9f);
        }
    }
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    NewOutPut.DifTarget = Color;
    NewOutPut.PosTarget = _Input.VIEWPOSITION;
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    
    return NewOutPut;
 }

