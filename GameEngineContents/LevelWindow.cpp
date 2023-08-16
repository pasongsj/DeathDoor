#include "PrecompileHeader.h"
#include "LevelWindow.h"

#include "CenterLevel.h"
#include "TestLevel.h"
#include "ServerTestLevel.h"

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
	ImGui::Text("CurLevel :");
	ImGui::SameLine();
	ImGui::Text(m_CurLevelName.c_str());
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0, 10));

	if (ImGui::Button("CenterLevel") && Level.get() != GetLevel())
	{
		m_CurLevelName = "CenterLevel";
		GameEngineCore::ChangeLevel("CenterLevel");
	}

	if (ImGui::Button("TestLevel") && Level.get() != GetLevel())
	{
		m_CurLevelName = "TestLevel";
		GameEngineCore::ChangeLevel("TestLevel");
	}

	if (ImGui::Button("ServerTestLevel") && Level.get() != GetLevel())
	{
		m_CurLevelName = "ServerTestLevel";
		GameEngineCore::ChangeLevel("ServerTestLevel");
	}

	if (ImGui::Button("MapEditorLevel") && Level.get() != GetLevel())
	{
		m_CurLevelName = "MapEditorLevel";
		GameEngineCore::ChangeLevel("MapEditorLevel");
	}

	ImGui::Text("CurCameraMode :");
	ImGui::SameLine();
	ImGui::Text(m_CurCameraMode.c_str());
	ImGui::Separator();

	if (ImGui::Button("FreeCamera") && Level.get() != GetLevel())
	{
		if (false == Level->GetMainCamera()->IsFreeCamera())
		{
			m_CurCameraMode = "Free Camera Mode";
		}
		else
		{
			m_CurCameraMode = "Play Mode";
		}
		Level->GetMainCamera()->SwtichFreeCamera();
	}
}

