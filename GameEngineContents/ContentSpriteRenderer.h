#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class ContentSpriteRenderer : public GameEngineSpriteRenderer
{

public:

	ContentSpriteRenderer();
	~ContentSpriteRenderer();

	ContentSpriteRenderer(const ContentSpriteRenderer& _Other) = delete;
	ContentSpriteRenderer(ContentSpriteRenderer&& _Other) noexcept = delete;
	ContentSpriteRenderer& operator=(const ContentSpriteRenderer& _Other) = delete;
	ContentSpriteRenderer& operator=(ContentSpriteRenderer&& _Other) noexcept = delete;

	void SetUVData(float4 _Data)
	{
		UVData = _Data;
	}
	std::shared_ptr<GameEngineRenderUnit> Unit;

protected:
	void Start() override;
private:
	float4 UVData = {1, 1, 0, 0 };
};

