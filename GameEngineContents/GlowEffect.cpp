#include "PrecompileHeader.h"

#include "GlowEffect.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCamera.h>

GlowEffect::GlowEffect()
{
}

GlowEffect::~GlowEffect()
{
}

void GlowEffect::Start(GameEngineRenderTarget* _Target)
{
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
	
	DetectMaskUnit.ShaderResHelper.SetTexture("DiffuseTexture", DiffuseTexture);
	DetectMaskUnit.ShaderResHelper.SetTexture("BlurTexture", BlurTexture);
	
	DetectMaskUnit.Render(_DeltaTime);
	DetectMaskUnit.ShaderResHelper.AllResourcesReset();

	////블러 적용
	BlurTarget->Clear();
	BlurTarget->Setting();

	BlurUnit.ShaderResHelper.SetTexture("DiffuseTexture", DetectMaskTarget->GetTexture(0));
	BlurUnit.Render(_DeltaTime);

	BlurUnit.ShaderResHelper.AllResourcesReset();
	
	std::shared_ptr<GameEngineTexture> ResultTex = BlurTarget->GetTexture(0);

	if(isDoubleBlur == true)
	{
		DoubleBlurTarget->Clear();
		DoubleBlurTarget->Setting();

		DoubleBlurUnit.ShaderResHelper.SetTexture("DiffuseTexture", BlurTarget->GetTexture(0));

		DoubleBlurUnit.Render(_DeltaTime);
		DoubleBlurUnit.ShaderResHelper.AllResourcesReset();

		ResultTex = DoubleBlurTarget->GetTexture(0);
	}

	LevelTarget->Setting();
	
	ColorMerge.ShaderResHelper.SetTexture("DiffuseTex", ResultTex);
	ColorMerge.Render(_DeltaTime);
	ColorMerge.ShaderResHelper.AllResourcesReset();
}

void GlowEffect::CreateTarget(float4 _BlurSize)
{
	DetectMaskUnit.SetMesh("FullRect");
	DetectMaskUnit.SetMaterial("DetectMask");

	DetectMaskTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);
	DetectMaskTarget->CreateDepthTexture();

	BlurSize = { 1600, 900 };
	DoubleBlurSize = { 800, 450 };

	BlurUnit.SetMesh("FullRect");
	BlurUnit.SetMaterial("AllBlur7x7");
	BlurUnit.ShaderResHelper.SetConstantBufferLink("Intensity", Intensity);
	BlurUnit.ShaderResHelper.SetConstantBufferLink("ScreenSize", BlurSize);
	BlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, BlurSize, float4::ZERONULL);
	BlurTarget->CreateDepthTexture();

	DoubleBlurUnit.SetMesh("FullRect");
	DoubleBlurUnit.SetMaterial("AllBlur7x7");
	DoubleBlurUnit.ShaderResHelper.SetConstantBufferLink("ScreenSize", DoubleBlurSize);
	DoubleBlurUnit.ShaderResHelper.SetConstantBufferLink("Intensity", Intensity);

	DoubleBlurTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DoubleBlurSize, float4::ZERONULL);

	BlurMergeUnit.SetMesh("FullRect");
	BlurMergeUnit.SetMaterial("LightMerge");

	ColorMerge.SetMesh("FullRect");
	ColorMerge.SetMaterial("DefferedColorMerge");
}