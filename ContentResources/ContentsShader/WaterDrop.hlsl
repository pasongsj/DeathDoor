#include "ContentTransform.fx"
#include "ContentRenderBaseValue.fx"
#include "ContentFunction.fx"
#include "Contentlight.fx"

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
    float4 DIFFUSELIGHT : TEXCOORD1;
    float4 SPECULALIGHT : TEXCOORD2;
    float4 AMBIENTLIGHT : TEXCOORD3;
    float4 POINTLIGHT : TEXCOORD4;
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
    
    float4 WorldPos = mul(InputPos, WorldMatrix);
    float4 WorldNormal = mul(InputNormal, WorldMatrix);
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

float4 ContentMeshTexture_PS(Output _Input) : SV_Target6
{
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    //Color = pow(Color, 2.2f);
    
    Color *= MulColor;
    Color += AddColor;
    
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
    
    float DiffuseAlpha = Color.w;
    Color = Color * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    Color.a = DiffuseAlpha;
    
    return ceil(Color * 3.0f) / 3.0f;
}

