#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameLogo : public GameEngineActor
{

public:

	GameLogo();
	~GameLogo();

	GameLogo(const GameLogo& _Other) = delete;
	GameLogo(GameLogo&& _Other) noexcept = delete;
	GameLogo& operator=(const GameLogo& _Other) = delete;
	GameLogo& operator=(GameLogo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineUIRenderer> LogoRender = nullptr;
};

