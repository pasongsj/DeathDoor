#include "ContentTransform.fx"
#include "ContentAnimation.fx"
#include "ContentLight.fx"
#include "ContentRenderBaseValue.fx"
#include "ContentFunction.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 WORLDPOSITION : POSITION1;
    
    float4 WVPPOSITION : POSITION5;
    float4 TEXCOORD : TEXCOORD;

    float4 NORMAL : NORMAL;
    float4 EYEVECTOR : TEXCOORD2;
};

cbuffer CamPos : register(b8)
{
    float4 CamPos;
};

cbuffer WaterHeight : register(b4)
{
    float4 WaterHeight;
};

Output ContentMeshDeferred_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    NewOutPut.WVPPOSITION = NewOutPut.POSITION;
    
    float4 EyeDir = InputPos - CamPos;
    NewOutPut.EYEVECTOR = mul(EyeDir, WorldView);
    
    NewOutPut.VIEWPOSITION = mul(InputPos, WorldView);
    NewOutPut.NORMAL = mul(InputNormal, WorldView);
    
    NewOutPut.WORLDPOSITION = mul(InputPos, WorldMatrix);
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);
Texture2D CrackTexture : register(t2);

SamplerState ENGINEBASE : register(s0);

struct DeferredOutPut
{
    float4 DifTarget : SV_Target1;
    float4 PosTarget : SV_Target2;
    float4 NorTarget : SV_Target3;
    float4 BlurTarget : SV_Target7;
};


cbuffer BlurColor : register(b5)
{
    float4 BlurColor;
};

cbuffer ClipData : register(b6)
{
    float2 MinClipData;
    float2 MaxClipData;
};

DeferredOutPut ContentMeshDeferred_PS(Output _Input)
{
    if (_Input.WORLDPOSITION.y < WaterHeight.x)
    {
        clip(-1);
    }
    
    DeferredOutPut NewOutPut = (DeferredOutPut) 0;
    
    if (saturate(_Input.TEXCOORD.x) < MinClipData.x && saturate(_Input.TEXCOORD.y) < MinClipData.y)
    {
        clip(-1);
    }
        
    if (saturate(_Input.TEXCOORD.x) > MaxClipData.x && saturate(_Input.TEXCOORD.y) > MaxClipData.y)
    {
        clip(-1);
    }
    
    
    //UV값 변경
    _Input.TEXCOORD.xy *= MulUV;
    _Input.TEXCOORD.xy += AddUV;
        
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    float4 MaskColor = (float4) 0.0f;
    
    //Crack
    if (UV_MaskingValue > 0.0f && _Input.TEXCOORD.x <= UV_MaskingValue && _Input.TEXCOORD.y <= UV_MaskingValue)
    {
        MaskColor = CrackTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
        
        float3 f3_BlurColor = BlurColor.rgb;
        
        if (MaskColor.a > 0.0f)
        {
            NewOutPut.BlurTarget = float4(Color.rgb, Color.a);
            Color = NewOutPut.BlurTarget;
            
            NewOutPut.BlurTarget = pow(NewOutPut.BlurTarget, 2.2f);
        }
    }
    
    //텍스쳐 색상 변경
    Color *= MulColor;
    Color += AddColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    //Fade
    if (Delta > 0.0f)
    {
        Color *= Fading(MaskTexture, ENGINEBASE, _Input.TEXCOORD.xy);
    }
    
    _Input.NORMAL.a = 1.0f;
    NewOutPut.NorTarget = _Input.NORMAL;
    
    float4 EyeDir = _Input.EYEVECTOR;
    EyeDir = normalize(EyeDir);
    
    float Ndv = saturate(dot(normalize(_Input.NORMAL), EyeDir));
    float Fresnel = 1 - pow(Ndv, 5.0f) *  5.0f;
    Color.rgb = (Color.rgb * Fresnel);
    
    NewOutPut.DifTarget = pow(Color, 2.2f);
    NewOutPut.PosTarget = _Input.VIEWPOSITION;

    
    return NewOutPut;
}

