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
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	
	void FadeInAndOut(float _Delta);

	float4 MaskValue = {0.0f, 0.85f, 0.0f, 0.0f};
	float4 DiffuseUV = {0.0f, 0.0f, 0.0f, 0.0f};

	struct DistortionData
	{
		float4 Distortion;
		float DistortionScale;
		float DistortionBias;
	};

	DistortionData Distortion;

	float4 BlurColor = float4::ZERO;
};

