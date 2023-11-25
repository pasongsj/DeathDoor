#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

class Content2DRenderer : public GameEngineRenderer
{

public:

	Content2DRenderer();
	~Content2DRenderer();

	Content2DRenderer(const Content2DRenderer& _Other) = delete;
	Content2DRenderer(Content2DRenderer&& _Other) noexcept = delete;
	Content2DRenderer& operator=(const Content2DRenderer& _Other) = delete;
	Content2DRenderer& operator=(Content2DRenderer&& _Other) noexcept = delete;

	void SetScaleToTexture(const std::string_view& _Name);
protected:
	void Start() override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;
};

