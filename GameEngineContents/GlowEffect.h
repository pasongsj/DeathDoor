#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class GlowEffect : public GameEnginePostProcess
{

public:

	GlowEffect();
	~GlowEffect();

	GlowEffect(const GlowEffect& _Other) = delete;
	GlowEffect(GlowEffect&& _Other) noexcept = delete;
	GlowEffect& operator=(const GlowEffect& _Other) = delete;
	GlowEffect& operator=(GlowEffect&& _Other) noexcept = delete;

	void SetLevel(std::weak_ptr<GameEngineLevel> _Level)
	{
		EffectedLevel = _Level;
	}

	std::shared_ptr<GameEngineRenderTarget> DetectMaskTarget = nullptr;
	std::shared_ptr<GameEngineRenderTarget> BlurTarget = nullptr;
	std::shared_ptr<GameEngineRenderTarget> DoubleBlurTarget = nullptr;

	//x는 DiffuseColor, y는 DiffuseLight, z는 SpecularLight, w는 AmbientLight
	void SetIntensity(float4 _Intensity)
	{
		Intensity.x = _Intensity.x;
		Intensity.y = _Intensity.y;
		Intensity.z = _Intensity.z;
		Intensity.w = _Intensity.w;
	}

	void Init(std::weak_ptr<GameEngineLevel> _Level, float4 _Intensity)
	{
		SetLevel(_Level);
		SetIntensity(_Intensity);
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:

	std::weak_ptr<GameEngineLevel> EffectedLevel;

	GameEngineRenderUnit DetectMaskUnit;
	GameEngineRenderUnit BlurMergeUnit;
	GameEngineRenderUnit BlurUnit;
	GameEngineRenderUnit DoubleBlurUnit;
	GameEngineRenderUnit ColorMerge;

	float4 Intensity = { 1.0f, 1.0f, 1.0f, 1.0f };
	float4 BlurSize = { 1600.0f, 900.0f };
	float4 DoubleBlurSize = { 1600.0f, 900.0f };
};

