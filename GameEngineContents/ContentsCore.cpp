#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "ServerWindow.h"
#include "LevelWindow.h"
#include "MapEditorWindow.h"

#include "CenterLevel.h"
#include "TestLevel.h"
#include "ServerTestLevel.h"
#include "MapEditorLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}



void ContentsCore::GameStart()
{
	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");	

	GameEngineGUI::GUIWindowCreate<LevelWindow>("LevelWindow");
	GameEngineGUI::GUIWindowCreate<ServerWindow>("ServerWindow");
	GameEngineGUI::GUIWindowCreate<MapEditorWindow>("MapEditorWindow");
	
	ContentsResourcesCreate();

	//InstallFont();

	GameEngineCore::CreateLevel<CenterLevel>();
	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<ServerTestLevel>();
	GameEngineCore::CreateLevel<MapEditorLevel>();

	GameEngineCore::ChangeLevel("CenterLevel");
}

void ContentsCore::GameEnd()
{
	//RemoveFont();
}


void ContentsCore::InstallFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Text");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == AddFontResourceA(File.GetFullPath().c_str()))
		{
			MsgAssert("폰트 설치에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

void ContentsCore::RemoveFont()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Text");
	std::vector<GameEngineFile> FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });
	for (GameEngineFile& File : FontFiles)
	{
		if (0 == RemoveFontResourceA(File.GetFullPath().data()))
		{
			MsgAssert("폰트 삭제에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}
