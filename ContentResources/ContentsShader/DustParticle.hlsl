#include "../../EngineResources/Shader/Transform.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};


OutPut ContentTexture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    
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

float4 ContentTexture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = NoiseTexture.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if(Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (Color.r > DeltaTime.x || Color.r > DeltaTime.y)
    {
        clip(-1);
    }
    
    float Alpha = 1 - Color.r;
        
    Color *= MulColor;
    Color += AddColor;
    
    Color.a = Alpha;
    
    return Color;
}