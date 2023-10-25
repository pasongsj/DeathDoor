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
#include <GameEngineCore/GameEngineCoreWindow.h>

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

void ContentLevel::LevelInit()
{
	CreateUI();
	SetPostPrecessEffect();
	CreateIMGUIDebugRenderTarget();
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

void ContentLevel::SetPostPrecessEffect()
{
	std::shared_ptr<GlowEffect> Effect = GetLevel()->GetMainCamera()->GetCamAllRenderTarget()->CreateEffect<GlowEffect>();
	Effect->Init(DynamicThis<GameEngineLevel>(), {1.0f, 0.0f, 0.0f, 0.0f});

	GameEngineCoreWindow::AddDebugRenderTarget(4, "Detect", Effect->DetectMaskTarget);

	std::shared_ptr<GammaCorrection> Effect2 = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
	std::shared_ptr<FXAA> Effect3 = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
}
