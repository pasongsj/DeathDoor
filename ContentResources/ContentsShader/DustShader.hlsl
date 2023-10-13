#include "../../EngineResources/Shader/Transform.fx"

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

Texture2D DustNoise : register(t0);
SamplerState WRAPSAMPLER : register(s0);

cbuffer ScaleBuffer : register(b0)
{
    float2 TextureScale;
    float2 UVScale;
}

cbuffer Delta : register(b1)
{
    float2 Speed;
    float2 Dir;
}

float4 ContentTexture_PS(OutPut _Value) : SV_Target0
{
    _Value.UV.xy = float2(_Value.UV.x * UVScale.x / TextureScale.x + Dir.x * Speed.x, _Value.UV.y * UVScale.y / TextureScale.y + Dir.y * Speed.y);
    
    float4 Color = DustNoise.Sample(WRAPSAMPLER, _Value.UV.xy);
    
    if(Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    Color *= 0.3f;
    
    return Color;
}