#pragma once
#include "PreCompileHeader.h"

enum class ContentsActorType
{
    ContentsFBXActor,

};


struct employeeShort {
    int ActorIndex;
    ContentsActorType ActorType;
    std::string FBXName;
    float4 LPos;
    float4 LRot;
    float4 LScale;
    float ScaleRatio;
    bool IsMoveable;

};