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
		Setter = _Setter;

		//중간에 세팅을 바꿀 수도 있는데, 만약 더 작아지면 안되니.
		if (Setter.MaxParticle > ParticleList.size())
		{
			ParticleList.resize(Setter.MaxParticle, nullptr);
		}
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

