#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class GrayScaleEffect : public GameEnginePostProcess
{

public:

	GrayScaleEffect();
	~GrayScaleEffect();

	GrayScaleEffect(const GrayScaleEffect& _Other) = delete;
	GrayScaleEffect(GrayScaleEffect&& _Other) noexcept = delete;
	GrayScaleEffect& operator=(const GrayScaleEffect& _Other) = delete;
	GrayScaleEffect& operator=(GrayScaleEffect&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineRenderTarget> GrayScaleTarget;

	GameEngineRenderUnit GrayScaleUnit;
	GameEngineRenderUnit MergeUnit;
};

