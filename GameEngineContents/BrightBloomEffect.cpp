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
	BlurSize = float4{ 1600.0f, 900.0f } / 16.0f;
	DoubleBlurSize = float4{ 1600.0f, 900.0f } / 8.0f;
	TripleBlurSize = float4{ 1600.0f, 900.0f } / 4.0f;
	QuadBlurSize = float4{ 1600.0f, 900.0f } / 2.0f;

	DetectTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	BlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	DoubleBlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);
	TripleBlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, TripleBlurSize, float4::ZERONULL);
	QuadBlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, QuadBlurSize, float4::ZERONULL);
	
	DownSampling2x2 = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize() / 2.0f, float4::ZERONULL);
	DownSampling4x4 = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize() / 4.0f, float4::ZERONULL);
	DownSampling8x8 = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize() / 8.0f, float4::ZERONULL);
	DownSampling16x16 = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize() / 16.0f, float4::ZERONULL);

	DetectUnit.SetMesh("FullRect");
	DetectUnit.SetMaterial("DetectLum");

	BlurUnit.SetMesh("FullRect");
	BlurUnit.SetMaterial("Blur");
	BlurUnit.ShaderResHelper.SetConstantBufferLink("BlurSize", UnitBlurSize);

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");

	SamplingUnit.SetMesh("FullRect");
	SamplingUnit.SetMaterial("Merge");
}

void BrightBloomEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	DetectTarget->Clear();
	DetectTarget->Setting();

	DetectUnit.ShaderResHelper.SetTexture("ScreenTexture", _Target->GetTexture(0));
	DetectUnit.Render(_DeltaTime);
	DetectUnit.ShaderResHelper.AllResourcesReset();
	
	DownSampling2x2->Clear();
	DownSampling2x2->Setting();

	SamplingUnit.ShaderResHelper.SetTexture("DiffuseTex", DetectTarget->GetTexture(0));
	SamplingUnit.Render(_DeltaTime);
	SamplingUnit.ShaderResHelper.AllResourcesReset();

	DownSampling4x4->Clear();
	DownSampling4x4->Setting();

	SamplingUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling2x2->GetTexture(0));
	SamplingUnit.Render(_DeltaTime);
	SamplingUnit.ShaderResHelper.AllResourcesReset();

	DownSampling8x8->Clear();
	DownSampling8x8->Setting();

	SamplingUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling4x4->GetTexture(0));
	SamplingUnit.Render(_DeltaTime);
	SamplingUnit.ShaderResHelper.AllResourcesReset();

	DownSampling16x16->Clear();
	DownSampling16x16->Setting();

	SamplingUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling8x8->GetTexture(0));
	SamplingUnit.Render(_DeltaTime);
	SamplingUnit.ShaderResHelper.AllResourcesReset();

	BlurTarget->Clear();
	BlurTarget->Setting();

	UnitBlurSize = BlurSize;

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling16x16->GetTexture(0));
	BlurUnit.Render(_DeltaTime);
	BlurUnit.ShaderResHelper.AllResourcesReset();

	DownSampling8x8->Merge(BlurTarget);

	DoubleBlurTarget->Clear();
	DoubleBlurTarget->Setting();

	UnitBlurSize = DoubleBlurSize;

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling8x8->GetTexture(0));
	BlurUnit.Render(_DeltaTime);
	BlurUnit.ShaderResHelper.AllResourcesReset();

	DownSampling4x4->Merge(DoubleBlurTarget);

	TripleBlurTarget->Clear();
	TripleBlurTarget->Setting();

	UnitBlurSize = TripleBlurSize;

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling4x4->GetTexture(0));
	BlurUnit.Render(_DeltaTime);
	BlurUnit.ShaderResHelper.AllResourcesReset();

	DownSampling2x2->Merge(TripleBlurTarget);

	QuadBlurTarget->Clear();
	QuadBlurTarget->Setting();

	UnitBlurSize = QuadBlurSize;

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTex", DownSampling2x2->GetTexture(0));
	BlurUnit.Render(_DeltaTime);
	BlurUnit.ShaderResHelper.AllResourcesReset();

	_Target->Setting();
	_Target->Merge(QuadBlurTarget);
}
