#include "PrecompileHeader.h"
#include "LevelWindow.h"

#include "CenterLevel.h"
#include "TestLevel.h"

LevelWindow::LevelWindow() 
{
}

LevelWindow::~LevelWindow() 
{
}

void LevelWindow::Start()
{
}

void LevelWindow::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	if (ImGui::Button("CenterLevel") && Level.get() != GetLevel())
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}

	if (ImGui::Button("TestLevel") && Level.get() != GetLevel())
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

