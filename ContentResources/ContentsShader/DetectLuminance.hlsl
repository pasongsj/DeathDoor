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

OutPut DetectLum_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D ScreenTexture : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 DetectLum_PS(OutPut _Value) : SV_Target0
{
    float4 Color = ScreenTexture.Sample(POINTSAMPLER, _Value.UV.xy);
    float Luminance = dot(Color.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    
    if(Luminance < 0.99f)
    {
        clip(-1);
    }
      
    return Color;
}