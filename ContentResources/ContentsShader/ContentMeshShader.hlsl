cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}


struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
  //float4 NORMAL : NORMAL;
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

cbuffer ColorOption : register(b1)
{
    float4 MulColor;
    float4 AddColor;
};

struct AniMat
{
    float4x4 Mat;
};


// 그래픽카드에서 이뤄지는것.
Output ContentMeshTexture_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    NewOutPut.POSITION = _Input.POSITION;
    NewOutPut.POSITION.w = 1.0f;
    // 자신의 로컬공간에서 애니메이션을 시키고
    // NewOutPut.POSITION = mul(_Input.POSITION, ArrAniMationMatrix[_Input.BLENDINDICES[0]].Mat);
    NewOutPut.POSITION = mul(NewOutPut.POSITION, WorldViewProjectionMatrix);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    //NewOutPut.NORMAL = _Input.NORMAL;
        
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState ENGINEBASE : register(s0);

float4 ContentMeshTexture_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(ENGINEBASE, _Input.TEXCOORD.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
   
    Color *= MulColor;
    Color += AddColor;
    
    //float4 Nor = normalize(_Input.NORMAL);
    //
    //if (Nor.z >= 0.5f)
    //{
    //    Color *= MulColor;
    //    Color += AddColor;
    //}
    //else
    //{
    //    float4 zero = { 0, 0, 0, 0 };
    //    float4 Zero_Alpha_1 = { 0.61, 0.67, 0.78, 1};
    //    
    //    Color *= zero;
    //    Color += Zero_Alpha_1;
    //}

    return Color;
}
