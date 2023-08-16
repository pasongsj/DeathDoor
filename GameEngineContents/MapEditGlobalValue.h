#pragma once
#include "PreCompileHeader.h"
#include <functional>
#include <string>


enum class ContentsActorType
{
    GameEngineActor,
    TestObject,
    Player
};


struct employeeShort {
    int ActorIndex;
    ContentsActorType ActorType;
    int ActorOrder;
    std::string FBXName;
    float4 LPos;
    float4 LRot;
    float4 LScale;
    float ScaleRatio;
    bool IsMoveable;

};