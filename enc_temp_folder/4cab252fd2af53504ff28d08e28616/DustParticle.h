#pragma once
#include "ParticleBase.h"

class DustParticle : public ParticleBase
{

public:

	DustParticle();
	~DustParticle();

	DustParticle(const DustParticle& _Other) = delete;
	DustParticle(DustParticle&& _Other) noexcept = delete;
	DustParticle& operator=(const DustParticle& _Other) = delete;
	DustParticle& operator=(DustParticle&& _Other) noexcept = delete;

	void SetColor(float4 _RGBA = { 0.815f, 0.576f, 0.427f, 1.0f });
	void SetGlow(float4 _GlowColor = float4::ZERO);

	void SetLoop(bool UVInit = false)
	{
		if (UVInit = true)
		{
			MaskValue.x = 0.0f;
		}

		UpdateFunc = std::bind(&DustParticle::FadeLoop, this, std::placeholders::_1);
	}

	void SetFadeInAndOut(bool UVInit = false)
	{
		if (UVInit = true)
		{
			MaskValue.x = 0.0f;
		}

		UpdateFunc = std::bind(&DustParticle::FadeInAndOut, this, std::placeholders::_1);
	}

	void SetFadeOut(bool UVInit = false)
	{
		if (UVInit = true)
		{
			MaskValue.x = 1.0f;
		}

		UpdateFunc = std::bind(&DustParticle::FadeOut, this, std::placeholders::_1);
	}

	void SetFadeIn(bool UVInit = false)
	{
		if (UVInit = true)
		{
			MaskValue.x = 0.0f;
		}

		UpdateFunc = std::bind(&DustParticle::FadeIn, this, std::placeholders::_1);
	}

	void SetFadeSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

	void FadeLoop(float _Delta);
	void FadeInAndOut(float _Delta);
	void FadeIn(float _Delta);
	void FadeOut(float _Delta);

	float4 MaskValue = {1.0f, 1.0f, 0.0f, 0.0f};
	float4 DiffuseUV = {0.0f, 0.0f, 0.0f, 0.0f};

	float4 Dir = float4::ZERO;

	struct DistortionData
	{
		float4 Distortion;
		float DistortionScale;
		float DistortionBias;
	};

	DistortionData Distortion;
	float LoopAngle = 0.0f;
	float FadeSpeed = 2.0f;

	float4 BlurColor = {1.0f, 1.0f, 1.0f, -1.0f };

	std::function<void(float)> UpdateFunc = nullptr;
};

