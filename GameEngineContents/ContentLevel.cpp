#include "PrecompileHeader.h"
#include "ContentLevel.h"
#include "Mouse.h"
#include "MPBar.h"
#include "HPBar.h"
#include "SkillSlot.h"
#include "GlowEffect.h"
#include "FXAA.h"
#include "GammaCorrection.h"
#include "BrightBloomEffect.h"
#include "AlphaGlowEffect.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

void ContentLevel::LevelInit(float4 _BlurSize)
{
	CreateUI();
	SetPostPrecessEffect(_BlurSize);
	CreateIMGUIDebugRenderTarget();
	CreatePivotActor();
}

void ContentLevel::CreateIMGUIDebugRenderTarget()
{
	GameEngineCoreWindow::AddDebugRenderTarget(0, "AllRenderTarget", GetMainCamera()->GetCamAllRenderTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(1, "LightRenderTarget", GetMainCamera()->GetDeferredLightTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(2, "MainCameraForwardTarget", GetMainCamera()->GetCamForwardTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(3, "DeferredTarget", GetMainCamera()->GetCamDeferrdTarget());
}

void ContentLevel::CreateUI()
{
	CreateActor<Mouse>();
	CreateActor<SkillSlot>(); 
	CreateActor<HpBar>();
	CreateActor<MpBar>();
}

void ContentLevel::SetPostPrecessEffect(float4 _BlurSize)
{
	Glow = GetLevel()->GetMainCamera()->GetCamAllRenderTarget()->CreateEffect<GlowEffect>();
	Glow->Init(DynamicThis<GameEngineLevel>(), {1.0f, 0.0f, 0.0f, 0.0f}, _BlurSize);

	AlphaGlow = GetLevel()->GetMainCamera()->GetCamAllRenderTarget()->CreateEffect<AlphaGlowEffect>();
	AlphaGlow->Init(DynamicThis<GameEngineLevel>(), { 1.0f, 0.0f, 0.0f, 0.0f }, _BlurSize);
	
	GameEngineCoreWindow::AddDebugRenderTarget(4, "aaa", AlphaGlow->BlurTarget);

	std::shared_ptr<GammaCorrection> Effect2 = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
	std::shared_ptr<FXAA> Effect3 = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
}

void ContentLevel::SetGlowScale(float _Distance)
{
	float4 BasicScale = { 1600, 900, 800, 450 };

	float Ratio = _Distance / 4000.0f;

	BasicScale *= 1.0f / Ratio;

	if (Glow != nullptr)
	{
		Glow->SetBlurScale(BasicScale);
	}
}

void ContentLevel::CreatePivotActor()
{
	PivotActor = CreateActor<GameEngineActor>();
}