struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut GrayScale_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 GrayScale_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(POINTSAMPLER, _Value.UV.xy);
   
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    float ColorAverage = (Color.r + Color.g + Color.b) / 3.0f;
    
    if (ColorAverage <= 0.5f)
    {
        ColorAverage = 0.0f;
    }
    else
    {
        ColorAverage = 1.0f;
    }
    
    Color = float4(ColorAverage, ColorAverage, ColorAverage, 1.0f);
    
    return Color;
}