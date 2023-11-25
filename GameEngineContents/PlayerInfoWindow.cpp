#include "PreCompileHeader.h"
#include "PlayerInfoWindow.h"
#include "Player.h"

PlayerInfoWindow::PlayerInfoWindow() 
{
}

PlayerInfoWindow::~PlayerInfoWindow() 
{
}
PlayerInfoWindow* PlayerInfoWindow::PlayerGUI;

void PlayerInfoWindow::Start()
{
	PlayerGUI = this;
	Off();
}

void PlayerInfoWindow::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	if (nullptr != Player::MainPlayer)
	{
		float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		std::string PositionText = "X : " + std::to_string(Pos.x) + " Y : " + std::to_string(Pos.y) + " Z : " + std::to_string(Pos.z);
		ImGui::Text(PositionText.c_str());
		ImGui::Separator();

		ImGui::Text("Current Player Mode : ");
		ImGui::SameLine();
		if (true == Player::MainPlayer->PlayerTestMode)
		{
			ImGui::Text("TEST");
		}
		else
		{
			ImGui::Text("GAME");
		}
		if (ImGui::Button("TEST"))
		{
			Player::MainPlayer->PlayerTestMode = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("GAME"))
		{
			Player::MainPlayer->PlayerTestMode = false;
		}
	}
}