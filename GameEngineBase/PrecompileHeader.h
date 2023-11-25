#pragma once

// Platform

#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h> // window.h보다 무조건 위쪽에 있어야 한다.
#include <Windows.h>

#include <memory>
#include <iostream>
#include <math.h>
#include <cmath>
#include <mutex>

// std
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <string_view>
#include <chrono>
#include <filesystem>
#include <functional>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리

using uint = unsigned int;



//PhysX 4.1
#pragma warning(disable : 4996)
#pragma warning(disable : 4099)
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysicsAPI.h>
#include <GameEngineCore/ThirdParty/PhysX_4_1/inc/PhysX/PxPhysXConfig.h>

#pragma comment (lib, "PhysX_static_64.lib")
#pragma comment (lib, "PhysXCharacterKinematic_static_64.lib")
#pragma comment (lib, "PhysXCommon_static_64.lib")
#pragma comment (lib, "PhysXExtensions_static_64.lib")
#pragma comment (lib, "PhysXFoundation_static_64.lib")
#pragma comment (lib, "PhysXPvdSDK_static_64.lib")
#pragma comment (lib, "PhysXCooking_static_64.lib")

#include <PhysXSDKSnippets/SnippetUtils.h>
#include <PhysXSDKSnippets/SnippetPrint.h>
#include <PhysXSDKSnippets/SnippetPVD.h>

