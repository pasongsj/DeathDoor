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

	void SetScaleDecrease(float4 _StartYScale, float _Speed)
	{
		isScaleDecrease = true;
		StartYScale = _StartYScale;
		DecreaseSpeed = _Speed;
	}

	void SetAutoMoveLerp(float4 _Start, float4 _End, float _Speed)
	{
		isAutoMoveLerp = true;

		LerpStartPos = _Start;
		LerpEndPos = _End;

		PosLerpSpeed = _Speed;
	}

	void SetScaleDecreaseLerp(float4 _Start, float4 _End, float _Speed)
	{
		isScaleDecreaseLerp = true;

		LerpStartScale = _Start;
		LerpEndScale = _End;

		ScaleLerpSpeed = _Speed;
	}

	void SetLocalMove()
	{
		isLocalMove = true;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	void AutoMove(float _Delta);
	void AutoMoveLerp(float _Delta);
	void ScaleDecrease(float _Delta);
	void ScaleDecreaseLerp(float _Delta);

	bool isLocalMove = false;

	bool isAutoMove = false;
	float4 MoveDir = float4::ZERO;
	float MoveSpeed = 0.0f;

	bool isScaleDecrease = false;
	float DecreaseSpeed = 0.0f;
	float4 StartYScale = float4::ZERO;

	bool isAutoMoveLerp = false;
	float4 LerpStartPos = float4::ZERO;
	float4 LerpEndPos = float4::ZERO;
	float PosLerpSpeed = 0.0f;
	float PosLerpRatio = 0.0f;

	bool isScaleDecreaseLerp = false;
	float4 LerpStartScale = float4::ZERO;
	float4 LerpEndScale = float4::ZERO;
	float ScaleLerpSpeed = 0.0f;
	float ScaleLerpRatio = 0.0f;
};

