#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

class ShockWave : public GameEngineRenderer
{

public:

	ShockWave();
	~ShockWave();

	ShockWave(const ShockWave& _Other) = delete;
	ShockWave(ShockWave&& _Other) noexcept = delete;
	ShockWave& operator=(const ShockWave& _Other) = delete;
	ShockWave& operator=(ShockWave&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;
};

