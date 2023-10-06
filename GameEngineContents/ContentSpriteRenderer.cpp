#include "PrecompileHeader.h"
#include "ContentSpriteRenderer.h"

ContentSpriteRenderer::ContentSpriteRenderer()
{
}

ContentSpriteRenderer::~ContentSpriteRenderer()
{
}

void ContentSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	std::shared_ptr<GameEngineRenderUnit> Unit = CreateRenderUnit();

	Unit->SetMesh("Rect");
}