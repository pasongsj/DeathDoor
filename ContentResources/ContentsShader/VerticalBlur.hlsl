struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut HorizonBlur_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // 화면 전체 범위
    return OutPutValue;
}

static float Blur[9] = { 0.1f, 0.18f, 0.55f, 0.9f, 1.0f, 0.9f, 0.55f, 0.18f, 0.1f };

Texture2D DiffuseTex : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 HorizonBlur_PS(OutPut _Value) : SV_Target0
{
    float2 PixelSize = float2(1.0f / 1600.0f, 1.0f / 900);
    // 현재 UV
    float2 PixelUvCenter = _Value.UV.xy;
    float2 StartUV = _Value.UV.xy + (-PixelSize * 4.0f);
    float2 CurUV = StartUV;
    
    float4 ResultColor = (float4) 0.0f;
    
    for (int y = 0; y < 9; ++y)
    {
        ResultColor += DiffuseTex.Sample(POINTSAMPLER, CurUV.xy) * Blur[y];
        CurUV.y += PixelSize.y;
    }
    
    if (ResultColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    return ResultColor;
}