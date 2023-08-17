#include "PrecompileHeader.h"
#include "ServerWindow.h"
#include "ConnectIDPacket.h"
#include "ObjectUpdatePacket.h"
#include "TestObject.h"
#include "ServerTestLevel.h"
#include "ConnectIDPacket.h"

GameEngineNet* ServerWindow::NetInst = nullptr;
ServerWindow* ServerWindow::ServerGUI = nullptr;

ServerWindow::ServerWindow()
{
	ServerGUI = this;
	IP.resize(1024);
	TestSendBuffer.resize(1024);
}

ServerWindow::~ServerWindow()
{
}

void ServerWindow::Start()
{
	ServerWindow::ServerGUI->Off();
}

void ServerWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	// IP.resize(128);
	// ImGui::PushID(1312321);
	std::string Text = "������ �������Դϴ�.";

	if (true == IsServer)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
		ImGui::InputText("##ServerText", &TestSendBuffer[0], TestSendBuffer.size());

		Text = "SendTest";
		if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
		{
			UINT StrLen = static_cast<UINT>(strlen(TestSendBuffer.c_str()));
			NetInst->Send(&TestSendBuffer[0], StrLen);
		}
		return;
	}

	Text = "Ŭ��� �������Դϴ�.";
	if (true == IsClient)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
		ImGui::InputText("##ClientText", &TestSendBuffer[0], TestSendBuffer.size());

		Text = "SendTest";
		if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
		{
			UINT StrLen = static_cast<UINT>(strlen(TestSendBuffer.c_str()));
			NetInst->Send(&TestSendBuffer[0], StrLen);
		}
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
	Text = "ȣ��Ʈ �ϱ�";
	if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
	{

		ServerPacketInit(Server);
		Server.ServerOpen(static_cast<unsigned short>(Port));
		ServerInit(Level);
		TestObject::MainTestObject->InitServerObject();


		IsServer = true;


		NetInst = &Server;


	}
	ImGui::Dummy(ImVec2(0, 10));
	Text = "Ŭ���̾�Ʈ�� �����ϱ�";
	if (ImGui::Button(GameEngineString::AnsiToUTF8(Text).c_str()))
	{
		ClientPacketInit(Client);
		IsClient = Client.Connect(IP, static_cast<unsigned short>(Port));

		NetInst = &Client;
	}

}

void ServerWindow::ServerInit(std::shared_ptr<GameEngineLevel> Level)
{
	Server.SetAcceptCallBack(
		[=](SOCKET _Socket, GameEngineNetServer* _Server)
		{
			// ������ ������Ը� ������ �Ѵ�.
			std::shared_ptr<ConnectIDPacket> Packet = std::make_shared<ConnectIDPacket>();

			int ID = GameEngineNetObject::CreateServerID();
			Packet->SetObjectID(ID);

			GameEngineSerializer Ser;
			Packet->SerializePacket(Ser);

			// �����ϰ� �ѹ� �� ���� ������ �Ἥ �������Ҷ�.
			GameEngineNet::Send(_Socket, Ser.GetConstCharPtr(), Ser.GetWriteOffSet());

			//// �̶� ��뿡�� ID�� ������.
			//std::shared_ptr<ConnectIDPacket> Packet = std::make_shared<ConnectIDPacket>();
			//std::shared_ptr<TestObject> NewTestObj = Level->CreateActor<TestObject>();

		}

	);
}


void ServerWindow::ServerPacketInit(GameEngineNetServer& _Net)
{

}

void ServerWindow::ClientPacketInit(GameEngineNetClient& _Net)
{
	_Net.Dispatcher.AddHandler<ConnectIDPacket>(PacketEnum::ConnectIDPacket,
		[](std::shared_ptr<ConnectIDPacket> _Packet)
		{
			//GetLevel()->

			int a = 0;
		}
	);
}