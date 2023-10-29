#include "PrecompileHeader.h"
#include "FXAA.h"

FXAA::FXAA()
{
}

FXAA::~FXAA()
{
}

void FXAA::Start(GameEngineRenderTarget* _Target)
{
	FXAATarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	
	FXAAUnit.SetMesh("FullRect");
	FXAAUnit.SetMaterial("FXAA");

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");
}

void FXAA::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	FXAATarget->Clear();
	FXAATarget->Setting();

	FXAAUnit.ShaderResHelper.SetTexture("ScreenTexture", _Target->GetTexture(0));
	FXAAUnit.Render(0.0f);
	FXAAUnit.ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Setting();

	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", FXAATarget->GetTexture(0));
	MergeUnit.Render(0.0f);
	MergeUnit.ShaderResHelper.AllResourcesReset();
}
