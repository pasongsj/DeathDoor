#include "PrecompileHeader.h"
#include "HitParticle.h"

#include <GameEngineBase/GameEngineRandom.h>

HitParticle::HitParticle()
{
}

HitParticle::~HitParticle()
{
}

void HitParticle::Start()
{
	ParticleBase::Start();

	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
	Unit->SetMaterial("ParticleBasic");

	Unit->ShaderResHelper.SetTexture("DiffuseTexture", "ParticleAlpha.png");
	
	float ScaleX = GameEngineRandom::MainRandom.RandomFloat(1.0f, 4.0f);
	
	GetTransform()->SetLocalScale({ ScaleX, 0.1f });
	Scale = ScaleX;

}

void HitParticle::Update(float _Delta)
{
	BillBoarding();

	Move(_Delta);

}

void HitParticle::Move(float _Delta)
{
	GetTransform()->AddLocalPosition( Dir * 5.0f * _Delta);

	Scale -= 5.0f * _Delta;
	if (Scale <= 0.0f)
	{
		Death();
	}

	GetTransform()->SetLocalScale({ Scale, 0.1f });
}
