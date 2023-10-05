#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class ServerTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ServerTestLevel();
	~ServerTestLevel();

	// delete Function
	ServerTestLevel(const ServerTestLevel& _Other) = delete;
	ServerTestLevel(ServerTestLevel&& _Other) noexcept = delete;
	ServerTestLevel& operator=(const ServerTestLevel& _Other) = delete;
	ServerTestLevel& operator=(ServerTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

};

