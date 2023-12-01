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
    float4 WORLDPOSITION : POSITION1;
    float4 TEXCOORD : TEXCOORD;
    float4 POINTLIGHT : TEXCOORD1;
    float4 DIFFUSELIGHT : TEXCOORD2;
    float4 SPECULALIGHT : TEXCOORD3;
    float4 AMBIENTLIGHT : TEXCOORD4;
};

cbuffer WaterHeight : register(b4)
{
    float4 WaterHeightInfo;
};

cbuffer IsOn : register(b5)
{
    bool isGamma;
    bool isHDR;
    bool2 padding;
};

cbuffer IsLight : register(b6)
{
    int isLight;
    int padding1;
    int padding2;
    int padding3;
};

Output ContentMeshForward_VS(Input _Input)
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

    NewOutPut.WORLDPOSITION = mul(InputPos, WorldMatrix);
    
    if (isLight == 1)
    {
        for (int Index = 0; Index < PointLightNum; Index++)
        {
            ResultPointLight += CalPointLight_ViewSpace(ViewPos, ViewNormal, PointLights[Index]);
        }
    
        NewOutPut.DIFFUSELIGHT = CalDiffuseLight(ViewPos, ViewNormal, AllLight[0]);
        NewOutPut.SPECULALIGHT = CalSpacularLight(ViewPos, ViewNormal, AllLight[0]);
        NewOutPut.AMBIENTLIGHT = CalAmbientLight(AllLight[0]);
        NewOutPut.POINTLIGHT = ResultPointLight;
    }
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);

SamplerState ENGINEBASE : register(s0);

float4 ContentMeshForward_PS(Output _Input) : SV_Target0
{
    if (_Input.WORLDPOSITION.y < WaterHeightInfo.x)
    {
        clip(-1);
    }
    
    //UV°ª º¯°æ
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
    
    float4 DiffuseColor = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
      
    if (isGamma == true)
    {
        DiffuseColor = pow(DiffuseColor, 2.2f);
    }
    
    DiffuseColor *= MulColor;
    DiffuseColor += AddColor;
    
     //Fade
    float4 FadeMask = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);

    if (Delta > 0.0f && FadeMask.r <= Delta)
    {
        clip(-1);
    }
    
    if (FadeMask.r > Delta && FadeMask.r <= Delta * 1.1f)
    {
        DiffuseColor = float4(FadeColor.r, FadeColor.g, FadeColor.b, 1.0f);
    }
    
    /**/
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
        
    if (isLight == 1)
    {
        float DiffuseAlpha = DiffuseColor.w;
        DiffuseColor = DiffuseColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
        DiffuseColor.a = DiffuseAlpha;
    }
    
    return DiffuseColor;
}

