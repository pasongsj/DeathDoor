#include "../../EngineResources/Shader/Transform.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
    float4 NORMAL : NORMAL;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 ViewPos : POSITION1;
    float4 ViewNormal : NORMAL;
    float4 UV : TEXCOORD;
    float4 ClipUV : TEXCOORD1;
};

OutPut HitCircle_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    
    OutPutValue.ViewPos = mul(_Value.Pos, WorldView);
    OutPutValue.ViewNormal = mul(_Value.NORMAL, WorldView);
    
    return OutPutValue;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

struct DefferedTarget
{
    float4 Color : SV_Target1;
    float4 Pos : SV_Target2;
    float4 Normal : SV_Target3;
    float4 Blur : SV_Target7;
};

DefferedTarget HitCircle_PS(OutPut _Value)
{
    DefferedTarget OutPutTarget = (DefferedTarget) 0;
    
    float4 TextureColor = DiffuseTexture.Sample(ENGINEBASE, _Value.UV.xy);
    
    if (TextureColor.a <= 0.0f)
    {
        clip(-1);
    }
    
    TextureColor *= 2.0f;
    
    OutPutTarget.Color = TextureColor;
    OutPutTarget.Blur = TextureColor;
    OutPutTarget.Pos = _Value.ViewPos;
    OutPutTarget.Normal = _Value.ViewNormal;
    
    return OutPutTarget;
}