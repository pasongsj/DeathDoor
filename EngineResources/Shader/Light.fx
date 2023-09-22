
struct LightData 
{
    float4x4 LightViewMatrix;
    float4x4 LightViewInverseMatrix;
    float4x4 LightProjectionMatrix;
    float4x4 LightProjectionInverseMatrix;
    float4x4 LightViewProjectionMatrix;
    float4x4 CameraViewInverseMatrix;
    float4 LightColor;
    float4 AmbientLight;
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
    float LightTargetSizeX;
    float LightTargetSizeY;
    float LightNear;
    float LightFar;
    float DifLightPower;
    float SpcLightPower;
    float AmbLightPower;
    float SpcPow;
    int LightType;
    float PointLightRange;
    int Temp2;
    int Temp3;
};

cbuffer LightDatas : register(b12)
{
    int LightCount;
    LightData AllLight[64];
};


struct PointLight
{
    float3 RGB;
    float4 Position;
    float MaxDist;
    float Intensity;
};

cbuffer AllPointLight : register(b13)
{
    int PointLightNum;
    float4x4 ViewInverse;
    PointLight PointLights[16];
};

float4 CalPointLight(float4 _Pos, float4 _Normal, PointLight _PointLight)
{
    float4 ResultPointLight = (float4) 0.0f;
    
    float4 InputNormal = _Normal;
    float4 InputPos = _Pos;
    
    InputPos.w = 1.0f;
    InputNormal.w = 1.0f;
    
    float4 WorldPos = mul(InputPos, ViewInverse);
    float4 WorldNormal = mul(InputNormal, ViewInverse);
    float4 WorldNormalDir = normalize(WorldNormal);
    
    float3 PointLightDir = _PointLight.Position.xyz - WorldPos.xyz;
    float3 PointLightNormal = normalize(PointLightDir);

    float PointLightDiffuse = max(0.0f, dot(WorldNormalDir.xyz, PointLightNormal));
    float PointLightDistance = distance(_PointLight.Position.xyz, WorldPos.xyz);
    
    float4 LightColor = float4(_PointLight.RGB, 1.0f);

    float4 PointLightColor = LightColor * PointLightDiffuse * (1.0f - saturate(PointLightDistance / _PointLight.MaxDist));
    
    ResultPointLight = _PointLight.Intensity * PointLightColor;
    
    return ResultPointLight;
}

float4 CalDiffuseLight(float4 _Pos,  float4 _Normal, LightData _Data)
{
    float4 ResultRatio = (float4) 0.0f;

    _Normal.xyz = normalize(_Normal.xyz); // N
    float4 LightRevDir;
    LightRevDir.xyz = normalize(_Data.ViewLightRevDir.xyz); // L
    
    ResultRatio = max(0.0f, dot(_Normal.xyz, LightRevDir.xyz));
    return ResultRatio * _Data.DifLightPower;
}

float4 CalSpacularLight(float4 _Pos, float4 _Normal, LightData _Data)
{
    float4 SpacularLight = (float4) 0.0f;
    
    _Normal.xyz = normalize(_Normal.xyz); // N
    _Data.ViewLightRevDir.xyz = normalize(_Data.ViewLightRevDir.xyz); // L
    
    float4 LightDir = _Data.ViewLightRevDir;
    
    // 반사벡터
    // 
    float3 Reflection = normalize(2.0f * _Normal.xyz * dot(LightDir.xyz, _Normal.xyz) - LightDir.xyz); //  N
    
    // 눈이 어디있냐
    float3 Eye = normalize(_Data.CameraPosition.xyz - _Pos.xyz); // L
    
    // 0 ~ 1
    float Result = max(0.0f, dot(Reflection.xyz, Eye.xyz));
    
    // SpacularLight.xyzw = Result;
    SpacularLight.xyzw = pow(Result, _Data.SpcPow);
    
    return SpacularLight;

}

float4 CalAmbientLight(LightData _LightData)
{
    return _LightData.AmbientLight;
}

float4 NormalTexCalculate(Texture2D NormalTex, SamplerState Smp, float4 UV, float4 _Tangent, float4 _BiNormal, float4 _Normal)
{
    float4 TexNormal = NormalTex.Sample(Smp, UV.xy);
    
    // 색상에는 음수색상이라는게 없어서
    // 노말을 계산한걸 텍스처로 만들때
    // +1 * 0.5f를 한다면 을 해버린다.
    // 그걸 원래대로 돌려주는 공식
    TexNormal = TexNormal * 2.0f - 1.0f;
    TexNormal.w = 0.0f;
    TexNormal = normalize(TexNormal);
    // 그냥 텍스처에서 가져온 normal 아직 회전안되었다.
    
    
    float4 Result = (float4) 0.0f;
    
    // 새로운 회전행렬을 만들어 낸다.
    // 탄젠트 스페이스라고 부른다.
    float3x3 TangentSpace = float3x3(_Tangent.xyz, _BiNormal.xyz, _Normal.xyz);
    Result.xyz = mul(TexNormal.xyz, TangentSpace);
    
    return Result;

}