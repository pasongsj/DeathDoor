#include "PrecompileHeader.h"
#include "CenterGui.h"

#include "CenterLevel.h"
#include "TestLevel.h"

CenterGui::CenterGui() 
{
}

CenterGui::~CenterGui() 
{
}

void CenterGui::Start()
{
}

void CenterGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
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

