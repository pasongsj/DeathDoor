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
	Unit->SetMaterial("ParticleBasic", RenderPath::Alpha);

	Unit->ShaderResHelper.SetTexture("DiffuseTexture", "ParticleAlpha.png");
}

void HitParticle::Update(float _Delta)
{
	BillBoarding();

	Move(_Delta);
	ScaleDecrease(_Delta);
}

void HitParticle::Move(float _Delta)
{
	Speed -= Accel * _Delta;
	if (Speed <= 0.0f)
	{
		Speed = 0.0f;
	}

	GetTransform()->AddWorldPosition( Dir * Speed * _Delta);
}

void HitParticle::ScaleDecrease(float _Delta)
{
	Scale -= FirstScale * 0.5f * _Delta;

	if (Scale <= 0.0f)
	{
		Death();
	}

	GetTransform()->SetWorldScale({ Scale, Scale / 10.0f });
}
