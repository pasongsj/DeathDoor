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
	std::shared_ptr<GameEngineRenderTarget> DoubleBlurTarget;
	std::shared_ptr<GameEngineRenderTarget> TripleBlurTarget;
	std::shared_ptr<GameEngineRenderTarget> QuadBlurTarget;

	std::shared_ptr<GameEngineRenderTarget> DownSampling2x2;
	std::shared_ptr<GameEngineRenderTarget> DownSampling4x4;
	std::shared_ptr<GameEngineRenderTarget> DownSampling8x8;
	std::shared_ptr<GameEngineRenderTarget> DownSampling16x16;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	//안티에일리어싱
	GameEngineRenderUnit DetectUnit;
	GameEngineRenderUnit BlurUnit;
	GameEngineRenderUnit MergeUnit;

	GameEngineRenderUnit SamplingUnit;

	float4 BlurSize = float4::ZERO;
	float4 DoubleBlurSize = float4::ZERO;
	float4 TripleBlurSize = float4::ZERO;
	float4 QuadBlurSize = float4::ZERO;

	float4 UnitBlurSize = float4::ZERO;
};

