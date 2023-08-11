#pragma once

#include <GameEnginePlatform/PrecompileHeader.h>

#include "GameEngineDebug3D.h"


#pragma warning(disable : 4996)
#include <GameEngineCore/ThirdParty/PhysX/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/PhysX/inc/PhysX/PxPhysicsAPI.h>

#pragma comment (lib, "PhysX_static_64.lib")
#pragma comment (lib, "PhysXCharacterKinematic_static_64.lib")
#pragma comment (lib, "PhysXCommon_static_64.lib")
#pragma comment (lib, "PhysXExtensions_static_64.lib")
#pragma comment (lib, "PhysXFoundation_static_64.lib")
#pragma comment (lib, "PhysXPvdSDK_static_64.lib")
#pragma comment (lib, "PhysXCooking_static_64.lib")