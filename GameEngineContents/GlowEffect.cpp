#include "PrecompileHeader.h"

#include "GlowEffect.h"
#include <GameEngineCore/GameEngineCamera.h>

GlowEffect::GlowEffect()
{
}

GlowEffect::~GlowEffect()
{
}

void GlowEffect::Start(GameEngineRenderTarget* _Target)
{
	DetectMaskUnit.SetMesh("FullRect");
	DetectMaskUnit.SetMaterial("DetectMask");


	DetectMaskTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	DetectMaskTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	DetectMaskTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	DetectMaskTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	
	BlurSize = { 800, 450 };
	DoubleBlurSize = { 1600, 900 };

	BlurUnit.SetMesh("FullRect");
	BlurUnit.SetMaterial("AllBlur7x7");
	BlurUnit.ShaderResHelper.SetConstantBufferLink("Intensity", Intensity);
	BlurUnit.ShaderResHelper.SetConstantBufferLink("ScreenSize", BlurSize);

	BlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	BlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	BlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	BlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	BlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);

	DoubleBlurUnit.SetMesh("FullRect");
	DoubleBlurUnit.SetMaterial("AllBlur7x7");
	DoubleBlurUnit.ShaderResHelper.SetConstantBufferLink("ScreenSize", DoubleBlurSize);
	DoubleBlurUnit.ShaderResHelper.SetConstantBufferLink("Intensity", Intensity);

	DoubleBlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);
	DoubleBlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);
	DoubleBlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);
	DoubleBlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);
	DoubleBlurTarget->AddNewTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);

	BlurMergeUnit.SetMesh("FullRect");
	BlurMergeUnit.SetMaterial("LightMerge");

	ColorMerge.SetMesh("FullRect");
	ColorMerge.SetMaterial("DefferedColorMerge");
}

void GlowEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	std::shared_ptr<GameEngineRenderTarget> LevelTarget = EffectedLevel.lock()->GetMainCamera()->GetCamAllRenderTarget();
	//diffuselight
	std::shared_ptr<GameEngineTexture> DiffuseLight = _Target->GetTexture(0);
	std::shared_ptr<GameEngineTexture> SpecularLight = _Target->GetTexture(1);
	std::shared_ptr<GameEngineTexture> AmbientLight = _Target->GetTexture(2);

	std::shared_ptr<GameEngineTexture> DiffuseTexture = LevelTarget->GetTexture(1);

	std::shared_ptr<GameEngineTexture> BlurTexture = LevelTarget->GetTexture(7);

	//블러할 부위를 검출
	DetectMaskTarget->Clear();
	DetectMaskTarget->Setting();
	
	DetectMaskUnit.ShaderResHelper.SetTexture("DifLightTexture", DiffuseLight);
	DetectMaskUnit.ShaderResHelper.SetTexture("SpcLightTexture", SpecularLight);
	DetectMaskUnit.ShaderResHelper.SetTexture("AmbLightTexture", AmbientLight);
	DetectMaskUnit.ShaderResHelper.SetTexture("DiffuseTexture", DiffuseTexture);
	DetectMaskUnit.ShaderResHelper.SetTexture("BlurTexture", BlurTexture);
	
	DetectMaskUnit.Render(_DeltaTime);
	DetectMaskUnit.ShaderResHelper.AllResourcesReset();

	////블러 적용
	BlurTarget->Clear();
	BlurTarget->Setting();

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTexture", DetectMaskTarget->GetTexture(0));
	BlurUnit.ShaderResHelper.SetTexture("DiffuseLight", DetectMaskTarget->GetTexture(1));
	BlurUnit.ShaderResHelper.SetTexture("SpecularLight", DetectMaskTarget->GetTexture(2));
	BlurUnit.ShaderResHelper.SetTexture("AmbientLight", DetectMaskTarget->GetTexture(3));

	BlurUnit.Render(_DeltaTime);

	BlurUnit.ShaderResHelper.AllResourcesReset();
	
	//블러 적용
	DoubleBlurTarget->Clear();
	DoubleBlurTarget->Setting();

	DoubleBlurUnit.ShaderResHelper.SetTexture("DiffuseTexture", BlurTarget->GetTexture(0));
	DoubleBlurUnit.ShaderResHelper.SetTexture("DiffuseLight", BlurTarget->GetTexture(1));
	DoubleBlurUnit.ShaderResHelper.SetTexture("SpecularLight", BlurTarget->GetTexture(2));
	DoubleBlurUnit.ShaderResHelper.SetTexture("AmbientLight", BlurTarget->GetTexture(3));
	
	DoubleBlurUnit.Render(_DeltaTime);
	DoubleBlurUnit.ShaderResHelper.AllResourcesReset();

	LevelTarget->Setting();
	
	ColorMerge.ShaderResHelper.SetTexture("DiffuseTex", BlurTarget->GetTexture(0));
	ColorMerge.Render(_DeltaTime);
	ColorMerge.ShaderResHelper.AllResourcesReset();

	_Target->Setting();
	
	//빛 배율 증가
	BlurMergeUnit.ShaderResHelper.SetTexture("DiffuseColor", DoubleBlurTarget->GetTexture(4));
	BlurMergeUnit.ShaderResHelper.SetTexture("DiffuseLight", DoubleBlurTarget->GetTexture(1));
	BlurMergeUnit.ShaderResHelper.SetTexture("SpecularLight", DoubleBlurTarget->GetTexture(2));
	BlurMergeUnit.ShaderResHelper.SetTexture("AmbientLight", DoubleBlurTarget->GetTexture(3));

	BlurMergeUnit.Render(_DeltaTime);
	BlurMergeUnit.ShaderResHelper.AllResourcesReset();

}
