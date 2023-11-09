#pragma once
#include <queue>

#include <GameEngineCore/PrecompileHeader.h>

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineDebug3D.h>

#include <GameEngineCore/GameEngineCollision.h>

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "ContentFBXRenderer.h"

//PhysX 4.1
//#pragma warning(disable : 4099)
//#pragma warning(disable : 4996)
//#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxConfig.h>
//#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysicsAPI.h>
//#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysXConfig.h>
//
//#pragma comment (lib, "PhysX_static_64.lib")
//#pragma comment (lib, "PhysXCharacterKinematic_static_64.lib")
//#pragma comment (lib, "PhysXCommon_static_64.lib")
//#pragma comment (lib, "PhysXExtensions_static_64.lib")
//#pragma comment (lib, "PhysXFoundation_static_64.lib")
//#pragma comment (lib, "PhysXPvdSDK_static_64.lib")
//#pragma comment (lib, "PhysXCooking_static_64.lib")

#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "PhysXDefault.h"

#include "ServerPacket.h"