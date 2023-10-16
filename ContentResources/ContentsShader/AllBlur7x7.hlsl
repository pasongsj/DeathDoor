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

OutPut Blur7x7_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

static float Gau[7][7] =
{
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
    { 0.000f, 0.002f, 0.012f, 0.002f, 0.012f, 0.002f, 0.000f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.001f, 0.020f, 0.109f, 0.172f, 0.109f, 0.020f, 0.001f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.000f, 0.002f, 0.012f, 0.020f, 0.012f, 0.002f, 0.000f },
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
};

//static float Gau[5][5] =
//{
//    { 1, 4, 6, 4, 1 },
//    { 4, 16, 24, 16, 4 },
//    { 6, 24, 36, 24, 6 },
//    { 4, 16, 24, 16, 4 },
//    { 1, 4, 6, 4, 1 }
//};

Texture2D DiffuseTexture : register(t0);
Texture2D DiffuseLight : register(t1);
Texture2D SpecularLight : register(t2);
Texture2D AmbientLight : register(t3);

SamplerState POINTSAMPLER : register(s0);

struct OutPutTarget
{
    float4 DiffuseTexture : SV_Target0;
    float4 DiffuseLight : SV_Target1;
    float4 SpecularLight : SV_Target2;
    float4 AmbientLight : SV_Target3;
    float4 BlurColor : SV_Target4;
};

cbuffer ScreenSize : register(b0)
{
    float4 ScreenSize;
};

cbuffer Intensity : register(b1)
{
    float4 Intensity;
};

OutPutTarget Blur7x7_PS(OutPut _Value) : SV_Target0
{
    float2 PixelSize = float2(1.0f / ScreenSize.x, 1.0f / ScreenSize.y);
    
    float2 StartUV = _Value.UV.xy + (-PixelSize * 3.0f);
    float2 CurUV = StartUV;
    
    float4 BlurColor = (float4) 0.0f;
    float4 TextureColor = (float4) 0.0f;
    float4 DifLight = (float4) 0.0f;
    float4 SpcLight = (float4) 0.0f;
    float4 AmbLight = (float4) 0.0f;

    
    for (int y = 0; y < 7; ++y)
    {
        for (int x = 0; x < 7; ++x)
        {
            float4 DiffuseColor = DiffuseTexture.Sample(POINTSAMPLER, CurUV.xy);
            
            if (DiffuseColor.a > 0.0f)
            {
                BlurColor = DiffuseColor;
            }
            
            TextureColor += DiffuseColor * Gau[y][x];
            DifLight += DiffuseLight.Sample(POINTSAMPLER, CurUV.xy) * Gau[y][x];
            SpcLight += SpecularLight.Sample(POINTSAMPLER, CurUV.xy) * Gau[y][x];
            AmbLight += AmbientLight.Sample(POINTSAMPLER, CurUV.xy) * Gau[y][x];
            
            CurUV.x += PixelSize.x;
        }
        
        CurUV.x = StartUV.x;
        CurUV.y += PixelSize.y;
    }
    
    if (TextureColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    TextureColor *= Intensity.x;
    
    DifLight = DifLight * Intensity.y;
    SpcLight = SpcLight * Intensity.z;
    AmbLight = AmbLight * Intensity.w;
    
    OutPutTarget Target = (OutPutTarget) 0.0f;
    
    Target.DiffuseTexture = TextureColor;
    Target.DiffuseLight = DifLight;
    Target.SpecularLight = SpcLight;
    Target.AmbientLight = AmbLight;
    Target.BlurColor = BlurColor;
    
    return Target;
}