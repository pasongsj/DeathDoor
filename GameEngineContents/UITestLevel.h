#pragma once
#include "PhysXLevel.h"

class UITestLevel : public PhysXLevel
{

public:

	UITestLevel();
	~UITestLevel();

	UITestLevel(const UITestLevel& _Other) = delete;
	UITestLevel(UITestLevel&& _Other) noexcept = delete;
	UITestLevel& operator=(const UITestLevel& _Other) = delete;
	UITestLevel& operator=(UITestLevel&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineLight> NewLight;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
};

