#pragma once
#include "ParticleManager.h"

class StaticParticleManager : public ParticleManager
{
public:

	StaticParticleManager();
	~StaticParticleManager();

	StaticParticleManager(const StaticParticleManager& _Other) = delete;
	StaticParticleManager(StaticParticleManager&& _Other) noexcept = delete;
	StaticParticleManager& operator=(const StaticParticleManager& _Other) = delete;
	StaticParticleManager& operator=(StaticParticleManager&& _Other) noexcept = delete;

	void SetPaticleSetter(const StaticParticleSetter& _Setter)
	{
		Setter.StandardDir = _Setter.StandardDir;
		Setter.RangeDir = _Setter.RangeDir;

		Setter.StandardScale = _Setter.StandardScale;
		Setter.RangeScale = _Setter.RangeScale;

		Setter.StandardPosition = _Setter.StandardPosition;
		Setter.RangePosition = _Setter.RangePosition;

		Setter.StandardSpeed = _Setter.StandardSpeed;
		Setter.range_Speed = _Setter.range_Speed;

		Setter.MaxParticle = _Setter.MaxParticle;
		Setter.EmitInterTime = _Setter.EmitInterTime;
		Setter.MaxLiveTime = _Setter.MaxLiveTime;

		EmitCount = _Setter.EmitInterTime;

		ParticleList.resize(Setter.MaxParticle, nullptr);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
private:

	void ParticleUpdate(float _Delta);
	void CreateParticle();
	void PushParticleToFront(std::shared_ptr<ParticleRenderer> _Particle);

	StaticParticleSetter Setter;
};

