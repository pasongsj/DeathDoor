#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	GameEngineCore::Start(hInstance, 
		ContentsCore::GameStart,
		ContentsCore::GameEnd,
		{100, 100},
		{1600,900}
	);

}