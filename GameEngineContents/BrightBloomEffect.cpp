#include "PrecompileHeader.h"
#include "BrightBloomEffect.h"

BrightBloomEffect::BrightBloomEffect()
{
}

BrightBloomEffect::~BrightBloomEffect()
{
}

void BrightBloomEffect::Start(GameEngineRenderTarget* _Target)
{
	BlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, {800, 450}, float4::ZERONULL);
	DetectTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	DetectUnit.SetMesh("FullRect");
	DetectUnit.SetMaterial("DetectLum");

	BlurUnit.SetMesh("FullRect");
	BlurUnit.SetMaterial("Blur");

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");
}

void BrightBloomEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	DetectTarget->Clear();
	DetectTarget->Setting();

	DetectUnit.ShaderResHelper.SetTexture("ScreenTexture", _Target->GetTexture(0));
	DetectUnit.Render(_DeltaTime);
	DetectUnit.ShaderResHelper.AllResourcesReset();

	BlurTarget->Clear();
	BlurTarget->Setting();

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTex", DetectTarget->GetTexture(0));
	BlurUnit.Render(_DeltaTime);
	BlurUnit.ShaderResHelper.AllResourcesReset();

	_Target->Setting();

	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", BlurTarget->GetTexture(0));
	MergeUnit.Render(_DeltaTime);
	MergeUnit.ShaderResHelper.AllResourcesReset();
}
