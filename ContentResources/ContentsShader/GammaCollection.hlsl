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

OutPut GammaCollection_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D ScreenTexture : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 GammaCollection_PS(OutPut _Value) : SV_Target0
{
    float4 Color = ScreenTexture.Sample(POINTSAMPLER, _Value.UV.xy);
   
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    float4 GammaColor = (float4) 0.0f;
    
    GammaColor.rgb = pow(Color.rgb, 2.2f);
    GammaColor.a = Color.a;
    
    return GammaColor;

}