#pragma once
#include "PreCompileHeader.h"
#include <functional>
#include <string>
const int MAX_NAME_LEN = 32;

enum class ContentsActorType
{
    GameEngineActor,
    TestObject,
    Player,
    SinkBox_4x4,
    SinkBox_8x8
};


struct SponeMapActor {
    //int ActorIndex = -1;
	int ActorType = 1;
    int ActorOrder = 0;
    float4 LocRot = float4::ZERO;
    float4 LocPos = float4::ZERO;
    float ScaleRatio = 1.0f;
    bool IsMoveable = false;
    unsigned int FBXNameLen = -1;
    std::string FBXName = "ActorFrozenBlock.fbx";
};