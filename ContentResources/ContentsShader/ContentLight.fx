
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

float4 CalPointLight_WorldSpace(float4 _Pos, float4 _Normal, PointLight _PointLight)
{
    float4 ResultPointLight = (float4) 0.0f;
    
    float4 WorldPos = _Pos;
    float4 WorldNormal = _Normal;
    
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
    return ResultRatio;
}

float4 CalSpacularLight(float4 _Pos, float4 _Normal, LightData _Data)
{
    float4 SpacularLight = (float4) 0.0f;
    
    _Normal.xyz = normalize(_Normal.xyz); // N
    _Data.ViewLightRevDir.xyz = normalize(_Data.ViewLightRevDir.xyz); // L
    
    float4 LightDir = _Data.ViewLightRevDir;
    
    // ¹Ý»çº¤ÅÍ
    // 
    float3 Reflection = normalize(2.0f * _Normal.xyz * dot(LightDir.xyz, _Normal.xyz) - LightDir.xyz); //  N
    
    // ´«ÀÌ ¾îµðÀÖ³Ä
    float3 Eye = normalize(_Data.CameraPosition.xyz - _Pos.xyz); // L
    
    // 0 ~ 1
    float Result = max(0.0f, dot(Reflection.xyz, Eye.xyz));
    
    // SpacularLight.xyzw = Result;
    SpacularLight.xyzw = pow(Result, 10);
    
    return SpacularLight;

}

float4 CalAmbientLight(LightData _LightData)
{
    return _LightData.AmbientLight;
}