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
	std::shared_ptr<GlowEffect> Effect = GetLevel()->GetMainCamera()->GetDeferredLightTarget()->CreateEffect<GlowEffect>();
	Effect->Init(DynamicThis<GameEngineLevel>(), {1.5f, 0.0f, 0.0f, 1.5f});

	//std::shared_ptr<BrightBloomEffect> Effect1 = GetLevel()->GetMainCamera()->GetCamTarget()->CreateEffect<BrightBloomEffect>();
	
	std::shared_ptr<FXAA> Effect3 = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
	std::shared_ptr<GammaCorrection> Effect2 = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
}
