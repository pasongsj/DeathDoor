#include "ContentTransform.fx"
#include "ContentAnimation.fx"
#include "ContentLight.fx"
#include "ContentRenderBaseValue.fx"

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
    float4 POINTLIGHT : TEXCOORD1;
    float4 DIFFUSELIGHT : TEXCOORD2;
    float4 SPECULALIGHT : TEXCOORD3;
    float4 AMBIENTLIGHT : TEXCOORD4;
};

cbuffer ColorOption : register(b1)
{
    float4 MulColor;
    float4 AddColor;
};

cbuffer UVData : register(b2)
{
    float2 MulUV;
    float2 AddUV;
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
    
    float4 WorldPos = mul(_Input.POSITION, WorldMatrix);
    float4 WorldNormal = mul(_Input.NORMAL, WorldMatrix);
    WorldNormal = normalize(WorldNormal);
    
    float4 ViewPos = mul(InputPos, WorldView);
    float4 ViewNormal = mul(InputNormal, WorldView);
    
    float4 ResultPointLight = (float4) 0.0f;
    
    for (int Index = 0; Index < PointLightNum; Index++)
    {
        ResultPointLight += CalPointLight_WorldSpace(WorldPos, WorldNormal, PointLights[Index]);
    }
    
    NewOutPut.DIFFUSELIGHT = CalDiffuseLight(ViewPos, ViewNormal, AllLight[0]);
    NewOutPut.SPECULALIGHT = CalSpacularLight(ViewPos, ViewNormal, AllLight[0]);
    NewOutPut.AMBIENTLIGHT = CalAmbientLight(AllLight[0]);
    NewOutPut.POINTLIGHT = ResultPointLight;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 ContentMeshTexture_PS(Output _Input) : SV_Target0
{
    //UV값 변경
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
    
    float4 DiffuseColor = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
      
    //텍스쳐 색상 변경
    DiffuseColor *= MulColor;
    DiffuseColor += AddColor;
    
    if (DiffuseColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    float4 DiffuseResultColor = (float4) 0.0f;
    
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
        
    float DiffuseAlpha = DiffuseColor.w;
    DiffuseResultColor = DiffuseColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    DiffuseResultColor.a = DiffuseAlpha;
    
    return DiffuseResultColor;
}

