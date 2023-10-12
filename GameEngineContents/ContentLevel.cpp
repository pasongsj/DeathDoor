#include "PrecompileHeader.h"
#include "ContentLevel.h"
#include "Mouse.h"
#include "MPBar.h"
#include "HPBar.h"
#include "SkillSlot.h"
#include "GlowEffect.h"
#include "FXAA.h"
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
	Effect->Init(DynamicThis<GameEngineLevel>(), {2.0f, 0.0f, 0.0f, 1.25f});

	std::shared_ptr<FXAA> Effect1 = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
}
