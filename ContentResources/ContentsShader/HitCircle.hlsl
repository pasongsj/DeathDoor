#include "ContentTransform.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
    float4 ClipUV : TEXCOORD1;
};

OutPut HitCircle_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 HitCircle_PS(OutPut _Value) : SV_Target6
{
    float4 TextureColor = DiffuseTexture.Sample(ENGINEBASE, _Value.UV.xy);
    
    if (TextureColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    //TextureColor.a = TextureColor.r - 0.1f;
    
    TextureColor.a = saturate(TextureColor.r - 0.2f);
    
    TextureColor.rgb = pow(TextureColor.rgb, 2.2f);
    TextureColor.rgb *= 8.0f;
    
    TextureColor = ToneMapping_ACES(TextureColor);
    
    return TextureColor;
}