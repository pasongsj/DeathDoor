#include "PrecompileHeader.h"
#include "HitEffect.h"
#include "HitCircle.h"
#include "HitParticle.h"

#include <GameEngineBase/GameEngineRandom.h>

HitEffect::HitEffect()
{
}

HitEffect::~HitEffect()
{
}

void HitEffect::Start()
{
	std::shared_ptr<HitCircle> Circle = CreateComponent<HitCircle>();
	Circle->SetAngle({ 0.0f, 0.0f, 0.0f});

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<HitParticle> New = CreateComponent<HitParticle>();
		float ZAngle = GameEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
		float4 XY = { cos(ZAngle / 180.0f * GameEngineMath::PIE), sin(ZAngle / 180.0f * GameEngineMath::PIE) };

		New->GetTransform()->AddLocalPosition({ XY.x, XY.y });
		New->SetAngle({ 0.0f, 0.0f, ZAngle });
		New->SetDir(XY.NormalizeReturn());
	}
}

void HitEffect::Update(float _Delta)
{
	if (GetLiveTime() > 1.0f)
	{
		Death();
	}
}
