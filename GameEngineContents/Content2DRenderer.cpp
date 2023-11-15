#include "PrecompileHeader.h"
#include "Content2DRenderer.h"

Content2DRenderer::Content2DRenderer()
{
}

Content2DRenderer::~Content2DRenderer()
{
}

void Content2DRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);

	if (nullptr == FindTex)
	{
		MsgAssert("존재하지 않는 이미지 입니다.");
		return;
	}

	float4 Scale = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1);
	GetTransform()->SetLocalScale(Scale);
}

void Content2DRenderer::Start()
{
	PushCameraRender(0);
	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
}
