#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class UITestLevel : public GameEngineLevel
{

public:

	UITestLevel();
	~UITestLevel();

	UITestLevel(const UITestLevel& _Other) = delete;
	UITestLevel(UITestLevel&& _Other) noexcept = delete;
	UITestLevel& operator=(const UITestLevel& _Other) = delete;
	UITestLevel& operator=(UITestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

};

