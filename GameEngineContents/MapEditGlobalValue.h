#pragma once
#include "PreCompileHeader.h"
#include <functional>
#include <string>
const int MAX_NAME_LEN = 32;

enum class ContentsMapMeshType
{
    Birchtree_03
};


struct SponeMapActor {
	int MeshType = 1;
    float4 LocRot = float4::ZERO;
    float4 LocPos = float4::ZERO;
    float ScaleRatio = 1.0f;
    unsigned int FBXNameLen = -1;
    std::string FBXName = "ActorFrozenBlock.fbx";
    unsigned int MeterialLen = -1;
    std::string MeterialName = "MeshTexture";
};