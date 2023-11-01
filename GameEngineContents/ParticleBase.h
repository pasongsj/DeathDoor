#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

class ParticleBase : public GameEngineRenderer
{

public:

	ParticleBase();
	~ParticleBase();

	ParticleBase(const ParticleBase& _Other) = delete;
	ParticleBase(ParticleBase&& _Other) noexcept = delete;
	ParticleBase& operator=(const ParticleBase& _Other) = delete;
	ParticleBase& operator=(ParticleBase&& _Other) noexcept = delete;

	void BillboardingOn()
	{
		isBillBoarding = true;
	}
	void BillboardingOff()
	{
		isBillBoarding = false;
	}

	void SetAngle(float4 _RotAngle);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void BillBoarding();
private:
	bool isBillBoarding = true;

	float4 RotAngle = float4::ZERO;
	std::shared_ptr<GameEngineRenderUnit> Unit;
};

