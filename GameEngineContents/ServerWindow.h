#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineNetServer.h>
#include <GameEngineBase/GameEngineNetClient.h>

// Ό³Έν :
class ServerWindow : public GameEngineGUIWindow
{
public:
	static ServerWindow* ServerGUI;
	// constrcuter destructer
	ServerWindow();
	~ServerWindow();

	// delete Function
	ServerWindow(const ServerWindow& _Other) = delete;
	ServerWindow(ServerWindow&& _Other) noexcept = delete;
	ServerWindow& operator=(const ServerWindow& _Other) = delete;
	ServerWindow& operator=(ServerWindow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;
	void ServerInit(std::shared_ptr<GameEngineLevel> Level);
	void ServerPacketInit(GameEngineNetServer& _Net);
	void ClientPacketInit(GameEngineNetClient& _Net);


private:
	GameEngineNetServer Server;
	GameEngineNetClient Client;
	static GameEngineNet* NetInst;

	bool IsServer = false;
	std::string IP = "127.0.0.1";
	int Port = 30000;
	bool IsClient = false;

	std::string TestSendBuffer = "TestString";
};

