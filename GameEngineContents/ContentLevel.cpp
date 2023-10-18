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
	Effect->Init(DynamicThis<GameEngineLevel>(), {2.25f, 0.0f, 0.0f, 0.0f});

	GameEngineCoreWindow::AddDebugRenderTarget(0, "CamTG", GetLevel()->GetMainCamera()->GetCamTarget());


	std::shared_ptr<GammaCorrection> Effect2 = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
	std::shared_ptr<FXAA> Effect3 = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
}
