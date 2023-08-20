#pragma once
#include <GameEngineCore/PrecompileHeader.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineDebug3D.h>

//PhysX 4.1
#pragma warning(disable : 4996)
#pragma warning(disable : 4099)
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysicsAPI.h>
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysXConfig.h>
#include "PhysXDefault.h"

#pragma comment (lib, "PhysX_static_64.lib")
#pragma comment (lib, "PhysXCharacterKinematic_static_64.lib")
#pragma comment (lib, "PhysXCommon_static_64.lib")
#pragma comment (lib, "PhysXExtensions_static_64.lib")
#pragma comment (lib, "PhysXFoundation_static_64.lib")
#pragma comment (lib, "PhysXPvdSDK_static_64.lib")
#pragma comment (lib, "PhysXCooking_static_64.lib")


#include "ContentsEnum.h"
#include "GlobalValue.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>

#include "ContentsEnum.h"