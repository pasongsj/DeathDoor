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
    // w나누기 해주고
    // viewport 행렬까지 레스터라이저에서 곱해준다.
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWNORMAL : NORMAL;
    float4 WORLDNORMAL : NORMAL1;
    float4 WORLDPOSITION : POSITION1;
};

struct PointLight
{
    float3 RGB;
    float4 Position;
    float MaxDist;
    float Intensity;
};

cbuffer AllPointLight : register(b3)
{
    int PointLightNum;
    float4x4 ViewInverse;
    PointLight PointLights[16];
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
    
    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    _Input.NORMAL.w = 0.0f;
    NewOutPut.VIEWNORMAL = mul(InputNormal, WorldView);
    NewOutPut.WORLDNORMAL = mul(InputNormal, WorldMatrix);
    NewOutPut.WORLDPOSITION = mul(InputPos, WorldMatrix);
    
    return NewOutPut;
}

struct OutputTarget
{
    float4 CamForwardTarget : SV_Target0;
    float4 BlurTarget : SV_Target6;
};

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);
SamplerState ENGINEBASE : register(s0);

OutputTarget ContentAniMeshForward_PS(Output _Input)
{
    OutputTarget PS_OutPut = (OutputTarget) 0.0f;
    
    float4 ResultPointLight = (float4) 0.0f;
    float3 WorldNormal = normalize(_Input.WORLDNORMAL);
    
    for (int i = 0; i < PointLightNum; i++)
    {
        float3 PointLightDir = PointLights[i].Position.xyz - _Input.WORLDPOSITION.xyz;
        float3 PointLightNormal = normalize(PointLightDir);
    
        float PointLightDiffuse = max(0.0f, dot(WorldNormal.xyz, PointLightNormal));
        float PointLightDistance = distance(PointLights[i].Position.xyz, _Input.WORLDPOSITION.xyz);
    
        float4 LightColor = float4(PointLights[i].RGB, 1.0f);

        float4 PointLightColor = LightColor * PointLightDiffuse * (1.0f - saturate(PointLightDistance / PointLights[i].MaxDist));
        
        ResultPointLight += PointLights[i].Intensity * PointLightColor;
    }
    
    float4 DiffuseRatio = CalDiffuseLight(_Input.VIEWPOSITION, _Input.VIEWNORMAL, AllLight[0]);
    float4 SpacularRatio = CalSpacularLight(_Input.VIEWPOSITION, _Input.VIEWNORMAL, AllLight[0]);
    float4 AmbientRatio = CalAmbientLight(AllLight[0]);
    
    float4 MaskColor = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    float4 MaskResultColor = (float4) 0.0f;
    
    float MaskAlpha = MaskColor.w;
    
    MaskResultColor = 2.0f * MaskColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    MaskResultColor += float4(0.8f, 0.0f, 0.5f, 1.0f);
    MaskResultColor.a = MaskAlpha;
    
    float4 DiffuseResultColor = (float4) 0.0f;
    float4 DiffuseColor = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    float DiffuseAlpha = DiffuseColor.w;
    DiffuseResultColor = DiffuseColor * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    DiffuseResultColor.a = DiffuseAlpha;
    
    //DiffuseResultColor = ceil(DiffuseResultColor * 10.0f) / 10.0f;
    
    PS_OutPut.CamForwardTarget = DiffuseResultColor;
    PS_OutPut.BlurTarget = MaskResultColor;
    
    return PS_OutPut;
}

