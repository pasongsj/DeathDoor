#include "PrecompileHeader.h"
#include "ContentUIFontRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>

ContentUIFontRenderer::ContentUIFontRenderer()
{
}

ContentUIFontRenderer::~ContentUIFontRenderer()
{
}

void ContentUIFontRenderer::SetFont(const std::string_view& _Font)
{
	Font = GameEngineFont::Find(_Font);
}

void ContentUIFontRenderer::SetText(const std::string_view& _Text)
{
	Text = _Text;
}

void ContentUIFontRenderer::Render(float _Delta)
{
	if (nullptr == Font)
	{
		return;
	}

	if ("" == Text)
	{
		return;
	}
	float4 Pos = GetTransform()->GetWorldPosition();
	GameEngineCamera* Camera = GetCamera();


	Pos *= Camera->GetView();
	Pos *= Camera->GetProjection();
	Pos.w = 1.f;
	Pos *= Camera->GetViewPort();


	Font->FontDraw(Text, Pos, FontScale, FontColor, FwTextFlag);

	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
}

void ContentUIFontRenderer::Start()
{
	PushCameraRender(100);
	Unit = CreateRenderUnit("Rect","Content2dTexture");


	Unit->RenderFunction = std::bind(&ContentUIFontRenderer::Render, this, std::placeholders::_1);
}