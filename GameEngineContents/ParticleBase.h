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

	void SetWorldMove()
	{
		isWorldMove = true;
	}

	void SetMoveInfo(float4 _Dir, float _Speed)
	{
		MoveDir = _Dir;
		MoveSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Move(float _Delta);

	void BillBoarding();
private:


	float4 MoveDir = float4::ZERO;
	float MoveSpeed = 0.0f;
	
	bool isWorldMove = false;
	bool isBillBoarding = true;

	float4 RotAngle = float4::ZERO;
	std::shared_ptr<GameEngineRenderUnit> Unit;
};

