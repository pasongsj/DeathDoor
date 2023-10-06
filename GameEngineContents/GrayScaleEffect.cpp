#include "PrecompileHeader.h"
#include "GrayScaleEffect.h"

GrayScaleEffect::GrayScaleEffect()
{
}

GrayScaleEffect::~GrayScaleEffect()
{

}

void GrayScaleEffect::Start(GameEngineRenderTarget* _Target)
{
	GrayScaleTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	GrayScaleUnit.SetMesh("FullRect");
	GrayScaleUnit.SetMaterial("GrayScale");
	GrayScaleUnit.ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");
	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", GrayScaleTarget->GetTexture(0));
}

void GrayScaleEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	GrayScaleTarget->Clear();
	GrayScaleTarget->Setting();

	GrayScaleUnit.Render(_DeltaTime);

	_Target->Clear();
	_Target->Setting();

	MergeUnit.Render(0.0f);
}
