#include "PrecompileHeader.h"
#include "GammaCorrection.h"

GammaCorrection::GammaCorrection()
{
}

GammaCorrection::~GammaCorrection()
{
}

void GammaCorrection::Start(GameEngineRenderTarget* _Target)
{
	GammaTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	GammaUnit.SetMesh("FullRect");
	GammaUnit.SetMaterial("GammaCorrection");

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");
}

void GammaCorrection::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	GammaTarget->Clear();
	GammaTarget->Setting();

	GammaUnit.ShaderResHelper.SetTexture("ScreenTexture", _Target->GetTexture(0));
	GammaUnit.Render(0.0f);
	GammaUnit.ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Setting();

	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", GammaTarget->GetTexture(0));
	MergeUnit.Render(0.0f);
	MergeUnit.ShaderResHelper.AllResourcesReset();
}
