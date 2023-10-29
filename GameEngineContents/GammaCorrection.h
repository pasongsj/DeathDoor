#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class GammaCorrection : public GameEnginePostProcess
{

public:

	GammaCorrection();
	~GammaCorrection();

	GammaCorrection(const GammaCorrection& _Other) = delete;
	GammaCorrection(GammaCorrection&& _Other) noexcept = delete;
	GammaCorrection& operator=(const GammaCorrection& _Other) = delete;
	GammaCorrection& operator=(GammaCorrection&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineRenderTarget> GammaTarget;
	GameEngineRenderUnit GammaUnit;
	GameEngineRenderUnit MergeUnit;
};

