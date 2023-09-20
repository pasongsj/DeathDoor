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
    float4 VIEWPOSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 WORLDPOSITION : POSITION3;
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

struct PointLight
{
    float3 RGB;
    float4 Position;
    float MaxDist;
    float Intensity;
};

cbuffer AllPointLight : register(b4)
{
    int PointLightNum;
    PointLight PointLights[16];
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

    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    _Input.NORMAL.w = 0.0f;
    NewOutPut.NORMAL = mul(InputNormal, WorldView);
    
    NewOutPut.WORLDPOSITION = mul(_Input.POSITION, WorldMatrix);
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 ContentMeshTexture_PS(Output _Input) : SV_Target0
{
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
    
    // 디퓨즈컬러
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    // 디퓨즈 라이트
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    float4 ResultPointLight = (float4) 0.0f;
    
    for (int i = 0; i < PointLightNum; i++)
    {
        float3 PointLightDir = PointLights[i].Position.xyz - _Input.WORLDPOSITION.xyz;
        float3 PointLightNormal = normalize(PointLightDir);
    
        float PointLightDiffuse = max(0.0f, dot(_Input.NORMAL.xyz, PointLightNormal));
        float PointLightDistance = distance(PointLights[i].Position.xyz, _Input.WORLDPOSITION.xyz);
    
        float4 LightColor = float4(PointLights[i].RGB, 1.0f);

        float4 PointLightColor = LightColor * PointLightDiffuse * (1.0f - saturate(PointLightDistance / PointLights[i].MaxDist));
        
        ResultPointLight += PointLights[i].Intensity * PointLightColor;
    }
    
    float4 DiffuseRatio = CalDiffuseLight(_Input.VIEWPOSITION, _Input.NORMAL, AllLight[0]);
    float4 SpacularRatio = CalSpacularLight(_Input.VIEWPOSITION, _Input.NORMAL, AllLight[0]);
    float4 AmbientRatio = CalAmbientLight(AllLight[0]);
    
    float A = Color.w;
    float4 ResultColor = Color * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
    ResultColor.a = A;
    
    ResultColor *= MulColor;
    ResultColor += AddColor;
    
    // Color += AllLight[0].LightColor;
    
    return ResultColor;
    
}

