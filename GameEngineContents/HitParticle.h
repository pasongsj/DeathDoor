#pragma once
#include "ParticleBase.h"

class HitParticle : public ParticleBase
{

public:

	HitParticle();
	~HitParticle();

	HitParticle(const HitParticle& _Other) = delete;
	HitParticle(HitParticle&& _Other) noexcept = delete;
	HitParticle& operator=(const HitParticle& _Other) = delete;
	HitParticle& operator=(HitParticle&& _Other) noexcept = delete;

	void Move(float _Delta);

	void SetDir(float4 _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;

	float4 Dir = float4::ZERO;
	float Scale = 0.0f;
};

