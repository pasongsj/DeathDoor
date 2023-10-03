struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD0;
};

OutPut ContentTexture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
        
    return OutPutValue;
}

cbuffer ColorOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}

Texture2D DiffuseTex : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 ContentTexture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(ENGINEBASE, _Value.UV.xy);
    Color = saturate(Color);
    
    return Color;
}