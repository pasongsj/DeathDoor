#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class DustRenderer : public GameEngineSpriteRenderer
{

public:

	DustRenderer();
	~DustRenderer();

	DustRenderer(const DustRenderer& _Other) = delete;
	DustRenderer(DustRenderer&& _Other) noexcept = delete;
	DustRenderer& operator=(const DustRenderer& _Other) = delete;
	DustRenderer& operator=(DustRenderer&& _Other) noexcept = delete;

	void SetUVScale(float _XScale, float _YScale)
	{
		ScaleBuffer.x = 1024.0f;
		ScaleBuffer.y = 1024.0f;
		ScaleBuffer.z = _XScale;
		ScaleBuffer.w = _YScale;
	}

	void SetMoveDir(float _DirX, float _DirY)
	{
		Delta.z = _DirX;
		Delta.w = _DirY;
	}

	void DustMove(float _DeltaTime, float _Speed)
	{
		Delta.x += _DeltaTime * _Speed;
		Delta.y += _DeltaTime * _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;

	float4 ScaleBuffer;
	float4 Delta;
};

