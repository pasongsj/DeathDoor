#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class WaterDrop : public GameEngineFBXRenderer
{

public:

	WaterDrop();
	~WaterDrop();

	WaterDrop(const WaterDrop& _Other) = delete;
	WaterDrop(WaterDrop&& _Other) noexcept = delete;
	WaterDrop& operator=(const WaterDrop& _Other) = delete;
	WaterDrop& operator=(WaterDrop&& _Other) noexcept = delete;

	void SetParabola(float4 _Dir, float _Gravity, float _Speed)
	{
		UpdateFunc = &WaterDrop::MoveToParabola;

		Dir = _Dir.NormalizeReturn();
		Gravity = _Gravity;
		Speed = _Speed;
	}

	void SetVerticalDrop(float _Gravity)
	{
		UpdateFunc = &WaterDrop::VerticalDrop;
		Gravity = _Gravity;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

	void MoveToParabola(float _Delta);
	void VerticalDrop(float _Delta);

	float4 Dir = float4::ZERO;
	float Gravity = 0.0f;
	float Speed = 0.0f;
	
	std::function<void(WaterDrop&, float)> UpdateFunc = nullptr;
};

