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
    
    _Input.NORMAL = NormalTexCalculate(NormalMap, WRAPSAMPLER, _Input.TEXCOORD, normalize(_Input.TANGENT), normalize(_Input.BINORMAL), normalize(_Input.NORMAL));
    
    NewOutPut.DifTarget = pow(Color, 2.2f);
    NewOutPut.PosTarget = _Input.VIEWPOSITION;
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    
    return NewOutPut;
}

