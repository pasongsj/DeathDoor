#include "PrecompileHeader.h"
#include "BossFrogWindow.h"

#include "BossFrog.h"

BossFrogWindow* BossFrogWindow::EditorGUI;


BossFrogWindow::BossFrogWindow() 
{
}

BossFrogWindow::~BossFrogWindow() 
{
}

void BossFrogWindow::Start()
{
	EditorGUI = this;
	Off();
}

void BossFrogWindow::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	if (nullptr != BossFrog::MainBoss)
	{
		float4 Pos = BossFrog::MainBoss->GetTransform()->GetWorldPosition();
		std::string PositionText = "X : " + std::to_string(Pos.x) + " Y : " + std::to_string(Pos.y) + " Z : " + std::to_string(Pos.z);
		ImGui::Text(PositionText.c_str());
		ImGui::Separator();
		float4 Forward = BossFrog::MainBoss->GetTransform()->GetWorldForwardVector();
		std::string ForwardText = "X : " + std::to_string(Forward.x) + " Y : " + std::to_string(Forward.y) + " Z : " + std::to_string(Forward.z);
		ImGui::Text(ForwardText.c_str());
	}
}