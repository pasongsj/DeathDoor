#pragma once
#include "ParticleBase.h"
#include <GameEngineBase/GameEngineRandom.h>

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
	void ScaleDecrease(float _Delta);
	void SetDir(float4 _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(float _Speed, float _Accel)
	{
		Speed = _Speed;
		Accel = _Accel;
	}

	void SetScaleRange(float _Min, float _Max)
	{
		float ScaleX = GameEngineRandom::MainRandom.RandomFloat(_Min, _Max);

		GetTransform()->SetWorldScale({ ScaleX, ScaleX / 10.0f });
		FirstScale = ScaleX;
		Scale = ScaleX;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;

	float4 Dir = float4::ZERO;
	float FirstScale = 0.0f;
	float Scale = 0.0f;
	float Speed = 10.0f;
	float Accel = 10.0f;
};

