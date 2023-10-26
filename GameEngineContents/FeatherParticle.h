#pragma once
#include "ParticleBase.h"

class FeatherParticle : public ParticleBase
{

public:

	FeatherParticle();
	~FeatherParticle();

	FeatherParticle(const FeatherParticle& _Other) = delete;
	FeatherParticle(FeatherParticle&& _Other) noexcept = delete;
	FeatherParticle& operator=(const FeatherParticle& _Other) = delete;
	FeatherParticle& operator=(FeatherParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float4 Dir = float4::ZERO;
	float Speed = 0.0f;
	float Accel = 0.0f;
};

