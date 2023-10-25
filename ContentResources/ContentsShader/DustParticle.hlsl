#include "../../EngineResources/Shader/Transform.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Normal : Normal;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};


OutPut ContentTexture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    
    OutPutValue.ViewPos = mul(_Value.Pos, WorldView);
    OutPutValue.ViewNormal = mul(_Value.Normal, WorldView);
    
    return OutPutValue;
}

Texture2D NoiseTexture : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

cbuffer MaskValue : register(b5)
{
    float2 DeltaTime;
    float Alpha;
    float Padding;
};

struct DefferedTarget
{
    float4 DiffuseColor : SV_Target1;
    float4 Position : SV_Target2;
    float4 Normal : SV_Target3;
};

DefferedTarget ContentTexture_PS(OutPut _Value)
{
    DefferedTarget OutPutTarget = (DefferedTarget) 0.0f;
    
    float4 Color = NoiseTexture.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if(Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (Color.r > DeltaTime.x || Color.r > DeltaTime.y)
    {
        clip(-1);
    }
    
    float Alpha = saturate(1 - Color.r);
        
    Color *= MulColor;
    Color += AddColor;
    
    Color.a = Alpha;
    
    OutPutTarget.DiffuseColor = saturate(Color);
    OutPutTarget.Position = _Value.ViewPos;
    OutPutTarget.Normal = _Value.ViewNormal;
    
    return OutPutTarget;
}