#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StartUI : public GameEngineActor
{

public:

	StartUI();
	~StartUI();

	StartUI(const StartUI& _Other) = delete;
	StartUI(StartUI&& _Other) noexcept = delete;
	StartUI& operator=(const StartUI& _Other) = delete;
	StartUI& operator=(StartUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _DelTa) override;
private:
	void LogoUpdate(float _Delta);

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround_Sky = nullptr;

	std::shared_ptr<class ContentSpriteRenderer> WhiteLine_Up = nullptr;
	std::shared_ptr<class ContentSpriteRenderer> WhiteLine_Down = nullptr;
	float AddUV = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Logo_Boomerang = nullptr;
	float RotAngle_Logo_Boomerang = 0.0f;
	float MoveAngle_Logo_Boomerang = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Logo_F = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Logo_U = nullptr;
	float ScaleAngle_Logo_FU = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Logo_Arrow = nullptr;

};

