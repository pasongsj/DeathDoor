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
    float4 TEXCOORD : TEXCOORD;
    float4 POINTLIGHT : TEXCOORD1;
    float4 DIFFUSELIGHT : TEXCOORD2;
    float4 SPECULALIGHT : TEXCOORD3;
    float4 AMBIENTLIGHT : TEXCOORD4;
};

cbuffer isLight : register(b5)
{
    int isLight;
    int padding1;
    int padding2;
    int padding3;
}

Output ContentAniMeshForward_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    if (IsAnimation != 0)
    {
        Skinning(InputPos, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
        InputPos.w = 1.0f;
        InputNormal.w = 0.0f;
    }
    
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    
    float4 ViewPos = mul(InputPos, WorldView);
    float4 ViewNormal = mul(InputNormal, WorldView);
    
    float4 ResultPointLight = (float4) 0.0f;
    
    if (isLight == 1)
    {
        for (int Index = 0; Index < PointLightNum; Index++)
        {
            ResultPointLight += CalPointLight_ViewSpace(ViewPos, ViewNormal, PointLights[Index]);
        }
        
        NewOutPut.DIFFUSELIGHT = CalDiffuseLight(ViewPos, ViewNormal, AllLight[0]);
        NewOutPut.SPECULALIGHT = CalSpacularLight(ViewPos, ViewNormal, AllLight[0]);
        NewOutPut.AMBIENTLIGHT = CalAmbientLight(AllLight[0]);
        NewOutPut.POINTLIGHT = ResultPointLight;
    }

    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);
Texture2D CrackTexture : register(t2);

SamplerState ENGINEBASE : register(s0);

cbuffer IsOn : register(b6)
{
    bool isGamma;
    bool isHDR;
    bool2 padding;
};

cbuffer CrackColor : register(b7)
{
    float4 CrackColor;
};

float4 ContentAniMeshForward_PS(Output _Input) : SV_Target0
{
    float4 ResultPointLight = _Input.POINTLIGHT;
    float4 DiffuseRatio = _Input.DIFFUSELIGHT;
    float4 SpacularRatio = _Input.SPECULALIGHT;
    float4 AmbientRatio = _Input.AMBIENTLIGHT;
    
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    if (isGamma == true)
    {
        Color = pow(Color, 2.2f);
    }

    float4 MaskColor = (float4) 0.0f;
    
    Color *= MulColor;
    Color += AddColor;
    
        
    //Fade
    float4 FadeMask = MaskTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);

    if (Delta > 0.0f && FadeMask.r <= Delta)
    {
        clip(-1);
    }
    
    if (FadeMask.r > Delta && FadeMask.r <= Delta * 1.1f)
    {
        Color = float4(FadeColor.r, FadeColor.g, FadeColor.b, 1.0f);
    }
    
    //Crack
    if (UV_MaskingValue > 0.0f && _Input.TEXCOORD.x <= UV_MaskingValue && _Input.TEXCOORD.y <= UV_MaskingValue)
    {
        MaskColor = CrackTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
        
        if (MaskColor.a > 0.0f)
        {
            Color = CrackColor;
            
            return Color;
        }
    }
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (isLight == 1)
    {
        float DiffuseAlpha = Color.w;
        Color = Color * (ResultPointLight + DiffuseRatio + SpacularRatio + AmbientRatio);
        Color.a = DiffuseAlpha;
    }
    
    return Color;
}
