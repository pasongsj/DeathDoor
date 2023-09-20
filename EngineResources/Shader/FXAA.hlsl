struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct VSOutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

VSOutPut FXAA_VS(Input _Value)
{
    VSOutPut OutPutValue = (VSOutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D ScreenTexture : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float GetLuma(float3 _Color)
{
    return sqrt(dot(_Color, float3(0.299f, 0.587f, 0.114f)));
}

#define EDGE_THRESHOLD_MIN 0.0312f
#define EDGE_THRESHOLD_MAX 0.125f

float4 FXAA_PS(VSOutPut _PSInput) : SV_Target0
{
    VSOutPut PSOutPut = (VSOutPut) 0.0f;
    
    float4 CenterColor = ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy);
    
    float LumaCenter = GetLuma(CenterColor.rgb);
    float2 PixelSize = float2(1.0f / 1600.0f, 1.0f / 900.0f);
    
    float LumaDown = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(0.0f, -PixelSize.y)).rgb);
    float LumaUp = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(0.0f, PixelSize.y)).rgb);
    float LumaLeft = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(PixelSize.x, 0.0f)).rgb);
    float LumaRight = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(-PixelSize.x, 0.0f)).rgb);

    float LumaMin = min(LumaCenter, min(min(LumaDown, LumaUp), min(LumaLeft, LumaRight)));
    float LumaMax = max(LumaCenter, max(max(LumaDown, LumaUp), max(LumaLeft, LumaRight)));
   
    float lumaRange = LumaMax - LumaMin;

    if (lumaRange < max(EDGE_THRESHOLD_MIN, LumaMax * EDGE_THRESHOLD_MAX))
    {
        return CenterColor;
    }
    
    float LumaDownLeft = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(-PixelSize.x, -PixelSize.y)).rgb);
    float LumaUpRight = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(PixelSize.x, PixelSize.y)).rgb);
    float LumaUpLeft = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(-PixelSize.x, PixelSize.y)).rgb);
    float LumaDownRight = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, _PSInput.UV.xy + float2(PixelSize.x, -PixelSize.y)).rgb);

    float LumaDownUp = LumaDown + LumaUp;
    float LumaLeftRight = LumaLeft + LumaRight;
    
    float LumaLeftCorners = LumaDownLeft + LumaUpLeft;
    float LumaDownCorners = LumaDownLeft + LumaDownRight;
    float LumaRightCorners = LumaDownRight + LumaUpRight;
    float LumaUpCorners = LumaUpRight + LumaUpLeft;
    
    float edgeHorizontal = abs(-2.0 * LumaLeft + LumaLeftCorners) + abs(-2.0 * LumaCenter + LumaDownUp) * 2.0 + abs(-2.0 * LumaRight + LumaRightCorners);
    float edgeVertical = abs(-2.0 * LumaUp + LumaUpCorners) + abs(-2.0 * LumaCenter + LumaLeftRight) * 2.0 + abs(-2.0 * LumaDown + LumaDownCorners);
    
    bool isHorizontal = (edgeHorizontal >= edgeVertical);
    
    float Luma1 = isHorizontal ? LumaDown : LumaLeft;
    float Luma2 = isHorizontal ? LumaUp : LumaRight;

    float gradient1 = Luma1 - LumaCenter;
    float gradient2 = Luma2 - LumaCenter;

    bool is1Steepest = abs(gradient1) >= abs(gradient2);

    float gradientScaled = 0.25 * max(abs(gradient1), abs(gradient2));
    
    float stepLength = isHorizontal ? PixelSize.y : PixelSize.x;

    float lumaLocalAverage = 0.0;

    if (is1Steepest)
    {
        stepLength = -stepLength;
        lumaLocalAverage = 0.5 * (Luma1 + LumaCenter);
    }
    else
    {
        lumaLocalAverage = 0.5 * (Luma2 + LumaCenter);
    }

    float2 currentUv = _PSInput.UV;
    
    if (isHorizontal)
    {
        currentUv.y += stepLength * 0.5;
    }
    else
    {
        currentUv.x += stepLength * 0.5;
    }
    
    float2 offset = isHorizontal ? float2(PixelSize.x, 0.0) : float2(0.0, PixelSize.y);

    float2 uv1 = currentUv - offset;
    float2 uv2 = currentUv + offset;

    float lumaEnd1 = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, uv1).rgb);
    float lumaEnd2 = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, uv2).rgb);
    
    lumaEnd1 -= lumaLocalAverage;
    lumaEnd2 -= lumaLocalAverage;

    bool reached1 = abs(lumaEnd1) >= gradientScaled;
    bool reached2 = abs(lumaEnd2) >= gradientScaled;
    bool reachedBoth = reached1 && reached2;

    if (!reached1)
    {
        uv1 -= offset;
    }
    if (!reached2)
    {
        uv2 += offset;
    }
    
    float Quality[12] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f, 4.0f, 8.0f };
    
    if (!reachedBoth)
    {
        for (int i = 0; i < 12; i++)
        {
            if (!reached1)
            {
                lumaEnd1 = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, uv1).rgb);
                lumaEnd1 = lumaEnd1 - lumaLocalAverage;
            }
            
            if (!reached2)
            {
                lumaEnd2 = GetLuma(ScreenTexture.Sample(WRAPSAMPLER, uv2).rgb);
                lumaEnd2 = lumaEnd2 - lumaLocalAverage;
            }
            
            reached1 = abs(lumaEnd1) >= gradientScaled;
            reached2 = abs(lumaEnd2) >= gradientScaled;
            
            reachedBoth = reached1 && reached2;

            if (!reached1)
            {
                uv1 -= offset * Quality[i];
            }
            if (!reached2)
            {
                uv2 += offset * Quality[i];
            }

            if (reachedBoth)
            {
                break;
            }
        }
    }
    
    float distance1 = isHorizontal ? (_PSInput.UV.x - uv1.x) : (_PSInput.UV.y - uv1.y);
    float distance2 = isHorizontal ? (uv2.x - _PSInput.UV.x) : (uv2.y - _PSInput.UV.y);

    bool isDirection1 = distance1 < distance2;
    float distanceFinal = min(distance1, distance2);

    float edgeThickness = (distance1 + distance2);

    float pixelOffset = -distanceFinal / edgeThickness + 0.5;
    
    bool isLumaCenterSmaller = LumaCenter < lumaLocalAverage;

    bool correctVariation = ((isDirection1 ? lumaEnd1 : lumaEnd2) < 0.0) != isLumaCenterSmaller;

    float finalOffset = correctVariation ? pixelOffset : 0.0;
    
    float lumaAverage = (1.0 / 12.0) * (2.0 * (LumaDownUp + LumaLeftRight) + LumaLeftCorners + LumaRightCorners);

    float subPixelOffset1 = clamp(abs(lumaAverage - LumaCenter) / lumaRange, 0.0, 1.0);
    float subPixelOffset2 = (-2.0 * subPixelOffset1 + 3.0) * subPixelOffset1 * subPixelOffset1;

    float subPixelOffsetFinal = subPixelOffset2 * subPixelOffset2 * 0.75f;

    finalOffset = max(finalOffset, subPixelOffsetFinal);
    
    float2 finalUv = _PSInput.UV;
    
    if (isHorizontal)
    {
        finalUv.y += finalOffset * stepLength;
    }
    else
    {
        finalUv.x += finalOffset * stepLength;
    }

    float4 finalColor = ScreenTexture.Sample(WRAPSAMPLER, finalUv.xy);
    
    return finalColor;
}