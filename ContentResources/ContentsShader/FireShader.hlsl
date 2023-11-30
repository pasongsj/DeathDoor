#include "ContentTransform.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;   
    
    float4 SCROLL_UV1 : TEXCOORD1;   
    float4 SCROLL_UV2 : TEXCOORD2;   
    float4 SCROLL_UV3 : TEXCOORD3;   
};

cbuffer FireNoise : register(b0)
{
    float FrameTime;
    float3 ScrollSpeeds;
    
    float3 Scales;
    
    //4바이트 단위로 데이터 채우기용
    float Padding;
};

OutPut Fire_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
        
    OutPutValue.UV = _Value.UV;
    
    OutPutValue.SCROLL_UV1 = _Value.UV * Scales.x;
    OutPutValue.SCROLL_UV1.y = OutPutValue.SCROLL_UV1.y + (FrameTime * ScrollSpeeds.x);
    
    OutPutValue.SCROLL_UV2 = _Value.UV * Scales.y;
    OutPutValue.SCROLL_UV2.y = OutPutValue.SCROLL_UV1.y + (FrameTime * ScrollSpeeds.y);
    
    OutPutValue.SCROLL_UV3 = _Value.UV * Scales.z;
    OutPutValue.SCROLL_UV3.y = OutPutValue.SCROLL_UV1.y + (FrameTime * ScrollSpeeds.z);
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t0);
Texture2D NoiseTexture : register(t1);
Texture2D AlphaTexture : register(t2);

SamplerState WRAPSAMPLER : register(s0);
SamplerState CLAMPSAMPLER : register(s1);

cbuffer DistortionData : register(b1)
{
    float2 Distortion1;
    float2 Distortion2;
    float2 Distortion3;
    float DistortionScale;
    float DistortionBias;
}

float4 Fire_PS(OutPut _Value) : SV_Target0
{
    float4 Noise1 = NoiseTexture.Sample(WRAPSAMPLER, _Value.SCROLL_UV1.xy);
    float4 Noise2 = NoiseTexture.Sample(WRAPSAMPLER, _Value.SCROLL_UV2.xy);
    float4 Noise3 = NoiseTexture.Sample(WRAPSAMPLER, _Value.SCROLL_UV3.xy);

    Noise1 = (Noise1 - 0.5f) * 2.0f;
    Noise2 = (Noise2 - 0.5f) * 2.0f;
    Noise3 = (Noise3 - 0.5f) * 2.0f;
   
    Noise1.xy = Noise1.xy * Distortion1;
    Noise2.xy = Noise2.xy * Distortion2;
    Noise3.xy = Noise3.xy * Distortion3;
    
    float4 FinalNoise = Noise1 + Noise2 + Noise3;
    
    float Perturb = ((1.0f - _Value.UV.y) * DistortionScale) + DistortionBias;
    float2 NoiseCoords = (FinalNoise.xy * Perturb) + _Value.UV.xy;
    
    float4 FireColor = DiffuseTexture.Sample(CLAMPSAMPLER, NoiseCoords.xy);
    float4 AlphaColor = AlphaTexture.Sample(CLAMPSAMPLER, NoiseCoords.xy);
    FireColor.a = AlphaColor.r;
    
    if (FireColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    float GrayScale = (FireColor.r + FireColor.g + FireColor.b) / 3.0f;
    
    if(GrayScale <= 0.45f)
    {
        clip(-1);
    }
    
    return FireColor * 4.0f;
}