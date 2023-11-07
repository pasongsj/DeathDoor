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
	Circle->BillboardingOff();

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<HitParticle> New = CreateComponent<HitParticle>();
		float ZAngle = GameEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
		float4 XY = { cos(ZAngle / 180.0f * GameEngineMath::PIE), sin(ZAngle / 180.0f * GameEngineMath::PIE) };

		New->GetTransform()->AddLocalPosition({ 0.5f * XY.x, 0.5f * XY.y });
		New->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, ZAngle });
		New->SetScaleRange(0.5f, 1.0f);
		New->SetDir(XY.NormalizeReturn());
		New->BillboardingOff();
	}
}

void HitEffect::Update(float _Delta)
{
	BillBoarding();

	if (GetLiveTime() > 1.0f)
	{
		//Death();
	}
}

void HitEffect::BillBoarding()
{
	std::shared_ptr<GameEngineCamera> Cam = GetLevel()->GetMainCamera();

	float4 CamDir = Cam->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
	CamDir.Normalize();

	float Dot = CamDir.x * CamDir.x + CamDir.z * CamDir.z;
	float AngleRad = acos(Dot);
	float AngleDeg = AngleRad * GameEngineMath::RadToDeg;

	GetTransform()->SetWorldRotation({ AngleDeg , 0.0f , 0.0f });
}