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

OutPut DetectMask_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t3);
Texture2D BlurTexture : register(t4);

SamplerState POINTSAMPLER : register(s0);

struct OutPutTarget
{
    float4 DiffuseTarget : SV_Target0;
};


    
OutPutTarget DetectMask_PS(OutPut _Value)
{
    float4 BlurColor = BlurTexture.Sample(POINTSAMPLER, _Value.UV.xy);
    
    if (BlurColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    float4 DiffuseColor = DiffuseTexture.Sample(POINTSAMPLER, _Value.UV.xy);
    
    if (abs(BlurColor.r - DiffuseColor.r) > 0.1f || abs(BlurColor.g - DiffuseColor.g) > 0.1f || abs(BlurColor.b - DiffuseColor.b) > 0.1f)
    {
        clip(-1);
    }
    
   
    OutPutTarget OutPut = (OutPutTarget) 0.0f;
    
    OutPut.DiffuseTarget = DiffuseColor;

    return OutPut;
}


