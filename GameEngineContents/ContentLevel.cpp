#include "PrecompileHeader.h"
#include "ContentLevel.h"
#include "Mouse.h"
#include "MPBar.h"
#include "HPBar.h"
#include "SkillSlot.h"
#include "GlowEffect.h"

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
	Effect->Init(DynamicThis<GameEngineLevel>(), 2.5f);
}
