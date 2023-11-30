#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class ToneMapping : public GameEnginePostProcess
{

public:

	ToneMapping();
	~ToneMapping();

	ToneMapping(const ToneMapping& _Other) = delete;
	ToneMapping(ToneMapping&& _Other) noexcept = delete;
	ToneMapping& operator=(const ToneMapping& _Other) = delete;
	ToneMapping& operator=(ToneMapping&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineRenderTarget> ToneMappingTarget;
	GameEngineRenderUnit ToneMappingUnit;
};

