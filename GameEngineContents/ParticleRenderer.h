#pragma once
#include "ParticleStruct.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>


class ParticleRenderer : public GameEngineFBXRenderer
{
	friend class StaticParticleManager;
	friend class DynamicParticleManager;
public:

	ParticleRenderer();
	~ParticleRenderer();

	ParticleRenderer(const ParticleRenderer& _Other) = delete;
	ParticleRenderer(ParticleRenderer&& _Other) noexcept = delete;
	ParticleRenderer& operator=(const ParticleRenderer& _Other) = delete;
	ParticleRenderer& operator=(ParticleRenderer&& _Other) noexcept = delete;

	void SetParticleInfo(const float4 _Dir, const float _Speed)
	{
		Dir = _Dir;
		Speed = _Speed;
	}

protected:
	void ParticlePosUpdate(float _Delta);

private:
	float4 Dir = { 0.0f, 0.0f, 0.0f };
	float Speed = 0.0f;
};

