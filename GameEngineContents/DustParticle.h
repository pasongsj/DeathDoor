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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	
	void FadeInAndOut(float _Delta);

	float4 MaskValue = {0.0f, 1.0f, 0.0f, 0.0f};
};

