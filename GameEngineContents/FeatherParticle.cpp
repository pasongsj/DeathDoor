#include "PrecompileHeader.h"
#include "FeatherParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

FeatherParticle::FeatherParticle()
{
}

FeatherParticle::~FeatherParticle()
{
}

void FeatherParticle::Start()
{
	ParticleBase::Start();
	SetBillBoardingType(BillBoardingType::XYZBillBoarding);

	GetUnit()->SetMesh("Rect");
	GetUnit()->SetMaterial("ParticleBasic", RenderPath::Alpha);

	GetUnit()->ShaderResHelper.SetTexture("DiffuseTexture", "FeatherParticle.png");

	GetTransform()->SetLocalScale({ 4.0f, 4.0f, 4.0f });

	float RandomX = GameEngineRandom::MainRandom.RandomFloat(-90.0f, 90.0f);
	float RandomY = GameEngineRandom::MainRandom.RandomFloat(-90.0f, 90.0f);
	float RandomZ = GameEngineRandom::MainRandom.RandomFloat(-90.0f, 90.0f);

	SetAngle({ RandomX, RandomY, 0 });

	Dir = { RandomX, -abs(RandomY), RandomZ };
	Dir.Normalize();

	Speed = 100.0f;
	Accel = 40.0f;
}

void FeatherParticle::Update(float _DeltaTime)
{
	BillBoarding();

	Speed -= Accel * _DeltaTime;
	GetTransform()->AddWorldPosition(Dir * Speed * _DeltaTime);

	float4 Scale = GetTransform()->GetLocalScale();
	GetTransform()->SetLocalScale({ Scale.x - 2.0f * _DeltaTime, Scale.y - 2.0f * _DeltaTime, 1.0f });

	if (GetLiveTime() >= 2.1f)
	{
		Death();
	}
}
