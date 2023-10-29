#pragma once
#include "ParticleBase.h"

class HitCircle : public ParticleBase
{

public:

	HitCircle();
	~HitCircle();

	HitCircle(const HitCircle& _Other) = delete;
	HitCircle(HitCircle&& _Other) noexcept = delete;
	HitCircle& operator=(const HitCircle& _Other) = delete;
	HitCircle& operator=(HitCircle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineRenderUnit> Unit;
};

