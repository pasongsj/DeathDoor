#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class BrightBloomEffect : public GameEnginePostProcess
{

public:

	BrightBloomEffect();
	~BrightBloomEffect();

	BrightBloomEffect(const BrightBloomEffect& _Other) = delete;
	BrightBloomEffect(BrightBloomEffect&& _Other) noexcept = delete;
	BrightBloomEffect& operator=(const BrightBloomEffect& _Other) = delete;
	BrightBloomEffect& operator=(BrightBloomEffect&& _Other) noexcept = delete;
	
	std::shared_ptr<GameEngineRenderTarget> DetectTarget;
	std::shared_ptr<GameEngineRenderTarget> BlurTarget;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	//안티에일리어싱
	GameEngineRenderUnit DetectUnit;
	GameEngineRenderUnit BlurUnit;
	GameEngineRenderUnit MergeUnit;
};

