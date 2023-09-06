#pragma once
#include "ParticleManager.h"

class DynamicParticleManager : public ParticleManager
{

public:

	DynamicParticleManager();
	~DynamicParticleManager();

	DynamicParticleManager(const DynamicParticleManager& _Other) = delete;
	DynamicParticleManager(DynamicParticleManager&& _Other) noexcept = delete;
	DynamicParticleManager& operator=(const DynamicParticleManager& _Other) = delete;
	DynamicParticleManager& operator=(DynamicParticleManager&& _Other) noexcept = delete;

	void SetPaticleSetter(const DynamicParticleSetter& _Setter)
	{
		Setter.StandardDir = _Setter.StandardDir;
		Setter.RangeDir = _Setter.RangeDir;

		Setter.StandardScale = _Setter.StandardScale;
		Setter.RangeScale = _Setter.RangeScale;

		Setter.StandardPosition = _Setter.StandardPosition;

		Setter.StandardSpeed = _Setter.StandardSpeed;
		Setter.range_Speed = _Setter.range_Speed;

		Setter.MaxParticle = _Setter.MaxParticle;
		Setter.EmitInterTime = _Setter.EmitInterTime;
		Setter.MaxLiveTime = _Setter.MaxLiveTime;

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


	DynamicParticleSetter Setter;
};

