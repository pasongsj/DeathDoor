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

	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
}