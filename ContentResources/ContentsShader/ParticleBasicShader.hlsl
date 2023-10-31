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
    float4 ViewPos : POSITION1;
    float4 ViewNormal : NORMAL;
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};

OutPut ContentTexture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    
    OutPutValue.ViewPos = mul(_Value.Pos, WorldView);
    OutPutValue.ViewNormal = mul(_Value.Normal, WorldView);
    
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

float4 ContentTexture_PS(OutPut _Value) : SV_Target6
{
    
    float4 Color = DiffuseTexture.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
        
    Color *= MulColor;
    Color += AddColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    return Color;
}