#include "ContentFunction.fx"
struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct Output
{
    float4 POSITION : SV_Position;
    float4 TEXCOORD : TEXCOORD;
};

Output ToneMapping_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.POSITION = _Input.POSITION;
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 ToneMapping_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    Color = ToneMapping_ACES(Color);
    
    return Color;
}