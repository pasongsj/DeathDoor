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
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 REFLECTPOS : POSITION2;
    float4 WVPPOSITION : POSITION5;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
};

cbuffer CamPos : register(b5)
{
    float4 CamPos;
}

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
    NewOutPut.BINORMAL = mul(float4(float3(0.0f, 0.0f, 1.0f), 0.0f), WorldView);
    NewOutPut.TANGENT = mul(float4(cross(NewOutPut.NORMAL.xyz, NewOutPut.BINORMAL.xyz), 0.0f), WorldView);
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D NormalMap : register(t1);

SamplerState WRAPSAMPLER : register(s0);

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
    
    //UV값 변경
    float4 InputUV = _Input.TEXCOORD;
    
    float4 UV_1 = (float4) 0.0f;
    float4 UV_2 = (float4) 0.0f;
    
    UV_1.xy = InputUV.xy * 2.0f + AddUV;
    UV_2.xy = InputUV.xy - AddUV * 0.3f;
    
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
    
    float4 Color = DiffuseTexture.Sample(WRAPSAMPLER, _Input.TEXCOORD.xy);
    float4 MaskColor = (float4) 0.0f;
    
    //텍스쳐 색상 변경
    Color *= MulColor;
    Color += AddColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    float4 Normal = NormalTexCalculate(NormalMap, WRAPSAMPLER, UV_1, normalize(_Input.TANGENT), normalize(_Input.BINORMAL), normalize(_Input.NORMAL));
    float4 Normal2 = NormalTexCalculate(NormalMap, WRAPSAMPLER, UV_2, normalize(_Input.TANGENT), normalize(_Input.BINORMAL), normalize(_Input.NORMAL));
    
    _Input.NORMAL = (Normal + Normal2) / 2.0f;
    
    NewOutPut.DifTarget = Color;
    //NewOutPut.BlurTarget = Color;
    NewOutPut.PosTarget = _Input.VIEWPOSITION;
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    
    return NewOutPut;
}

