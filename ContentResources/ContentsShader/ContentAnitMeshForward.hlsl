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
    float4 TEXCOORD : TEXCOORD;
    float4 POINTLIGHT : TEXCOORD1;
    float4 DIFFUSELIGHT : TEXCOORD2;
    float4 SPECULALIGHT : TEXCOORD3;
    float4 AMBIENTLIGHT : TEXCOORD4;
};


Output ContentAniMeshForward_VS(Input _Input)
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

struct OutputTarget
{
    float4 CamForwardTarget : SV_Target0;
    float4 BlurTarget : SV_Target7;
};

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);
Texture2D CrackTexture : register(t2);

SamplerState ENGINEBASE : register(s0);

OutputTarget ContentAniMeshForward_PS(Output _Input)
{
    OutputTarget PS_OutPut = (OutputTarget) 0.0f;
    
    float4 MaskColor = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    float4 MaskResultColor = (float4) 0.0f;
    
    float MaskAlpha = MaskColor.a;
    
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
    
    //Crack
    MaskResultColor = MaskColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    MaskResultColor += float4(0.8f, 0.0f, 0.5f, 1.0f);
    MaskResultColor.a = MaskAlpha;
    
    float4 DiffuseResultColor = (float4) 0.0f;
    float4 DiffuseColor = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    //Fade
    if (Delta > 0.0f)
    {
        DiffuseColor *= Fading(MaskTexture, ENGINEBASE, _Input.TEXCOORD.xy);
    }
    
    float DiffuseAlpha = DiffuseColor.w;
    DiffuseResultColor = DiffuseColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    DiffuseResultColor.a = DiffuseAlpha;
    
    PS_OutPut.CamForwardTarget = DiffuseResultColor;
    PS_OutPut.BlurTarget = MaskResultColor;
    
    return PS_OutPut;
}

