#include "PrecompileHeader.h"
#include "ServerWindow.h"

GameEngineNet* ServerWindow::NetInst = nullptr;

ServerWindow::ServerWindow()
{
	IP.resize(1024);
}

ServerWindow::~ServerWindow()
{
}

void ServerWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	// IP.resize(128);
	// ImGui::PushID(1312321);
	std::string Text = "서버로 동작중입니다.";

	if (true == IsServer)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
		return;
	}

	Text = "클라로 동작중입니다.";
	if (true == IsClient)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
		return;
	}



	Text = "Port :";
	ImGui::Text(Text.c_str());
	ImGui::SameLine();
	ImGui::InputInt("##Port", &Port);

	Text = "IP :";
	ImGui::Text(Text.c_str());
	ImGui::SameLine();
	ImGui::InputText("##IP", &IP[0], IP.size());
	// IP.resize(128);
	// ImGui::PushID(1312321);
	// ImGui::PopID();

	ImGui::Dummy(ImVec2(0, 10));
	ImGui::NextColumn();
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0, 10));
	Text = "호스트 하기";
	if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
	{
		Server.ServerOpen(static_cast<unsigned short>(Port));
		IsServer = true;
		NetInst = &Server;

	}
	ImGui::Dummy(ImVec2(0, 10));
	Text = "클라이언트로 접속하기";
	if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
	{
		IsClient = Client.Connect(IP, static_cast<unsigned short>(Port));
		NetInst = &Client;
	}

}