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
    
    for (int Index = 0; Index < PointLightNum; Index++)
    {
        ResultPointLight += CalPointLight_WorldSpace(WorldPos, WorldNormal, PointLights[Index]);
    }
    
    NewOutPut.DIFFUSELIGHT = CalDiffuseLight(ViewPos, ViewNormal, AllLight[0]);
    NewOutPut.SPECULALIGHT = CalSpacularLight(ViewPos, ViewNormal, AllLight[0]);
    NewOutPut.AMBIENTLIGHT = CalAmbientLight(AllLight[0]);
    NewOutPut.POINTLIGHT = ResultPointLight;
    NewOutPut.WORLDPOSITION = mul(InputPos, WorldMatrix);
    
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
    
    //UV값 변경
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
    
    float4 DiffuseColor = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
      
    //텍스쳐 색상 변경
    DiffuseColor *= MulColor;
    DiffuseColor += AddColor;
    
    if(isGamma == true)
    {
        DiffuseColor = pow(DiffuseColor, 2.2f);
    }
    
    //Fade
    if (Delta > 0.0f)
    {
        DiffuseColor *= Fading(MaskTexture, ENGINEBASE, _Input.TEXCOORD.xy);
    }
    
    /**/
    float4 DiffuseResultColor = (float4) 0.0f;
    
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
        
    float DiffuseAlpha = DiffuseColor.w;
    DiffuseResultColor = DiffuseColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    DiffuseResultColor.a = DiffuseAlpha;
    
    //툰쉐이더  
    //ResultColor = ceil(ResultColor * 5.0f) / 5.0f;
    if(isHDR == true)
    {
        DiffuseResultColor = ToneMapping_ACES(DiffuseResultColor);
    }
    
    return DiffuseResultColor;
}

