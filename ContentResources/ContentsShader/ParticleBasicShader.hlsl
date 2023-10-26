#include "../../EngineResources/Shader/Transform.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Normal : Normal;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 ViewPos : POSITION1;
    float4 ViewNormal : NORMAL;
    float4 UV : TEXCOORD0;
    float4 ClipUV : TEXCOORD1;
};

OutPut ContentTexture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    
    OutPutValue.ViewPos = mul(_Value.Pos, WorldView);
    OutPutValue.ViewNormal = mul(_Value.Normal, WorldView);
    
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

struct DefferedTarget
{
    float4 DiffuseColor : SV_Target1;
    float4 Position : SV_Target2;
    float4 Normal : SV_Target3;
};

DefferedTarget ContentTexture_PS(OutPut _Value)
{
    DefferedTarget OutPutTarget = (DefferedTarget) 0.0f;
    
    float4 Color = DiffuseTexture.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
        
    Color *= MulColor;
    Color += AddColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    OutPutTarget.DiffuseColor = Color;
    OutPutTarget.Position = _Value.ViewPos;
    OutPutTarget.Normal = _Value.ViewNormal;
    
    return OutPutTarget;
}