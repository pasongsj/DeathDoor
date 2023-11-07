#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class Particle3D : public GameEngineFBXRenderer
{

public:

	Particle3D();
	~Particle3D();

	Particle3D(const Particle3D& _Other) = delete;
	Particle3D(Particle3D&& _Other) noexcept = delete;
	Particle3D& operator=(const Particle3D& _Other) = delete;
	Particle3D& operator=(Particle3D&& _Other) noexcept = delete;

	void SetAutoMove(float4 _Dir, float _Speed)
	{
		isAutoMove = true;

		MoveDir = _Dir;
		MoveSpeed = _Speed;
	}

	void SetScaleDecrease(float _StartYScale, float _Speed)
	{
		isScaleDecrease = true;
		StartYScale = _StartYScale;
		DecreaseSpeed = _Speed;
	}


protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	void AutoMove(float _Delta);
	void ScaleDecrease(float _Delta);

	bool isAutoMove = true;
	float4 MoveDir = float4::ZERO;
	float MoveSpeed = 0.0f;

	bool isScaleDecrease = false;
	float DecreaseSpeed = 0.0f;
	float StartYScale = 0.0f;
};

