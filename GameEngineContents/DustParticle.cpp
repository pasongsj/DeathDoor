#include "PrecompileHeader.h"
#include "DustParticle.h"

DustParticle::DustParticle()
{
}

DustParticle::~DustParticle()
{
}

void DustParticle::Start()
{
	ParticleBase::Start();

	GetUnit()->SetMesh("Rect");
	GetUnit()->SetMaterial("DustParticle");

	GetUnit()->ShaderResHelper.SetTexture("NoiseTexture", "ParticleCloudBlack.png");
	GetUnit()->ShaderResHelper.SetConstantBufferLink("MaskValue", MaskValue);
	GetUnit()->Color.MulColor = float4::ZERONULL;
	GetUnit()->Color.PlusColor = float4{ 0.878f, 0.721f, 0.541f, 1.0f };

	GetTransform()->SetLocalScale({ 5.0f, 5.0f, 1.0f });

	SetAngle({ 55.0f, 0.0f, 0.0f });
}

void DustParticle::Update(float _Delta)
{
	BillBoarding();

	FadeInAndOut(_Delta);
}

void DustParticle::Render(float _Delta)
{
}

void DustParticle::FadeInAndOut(float _Delta)
{
	if (MaskValue.x < 1.0f)
	{
		MaskValue.x += 1.5f * _Delta;
		MaskValue.z = MaskValue.x;
	}
	else
	{
		MaskValue.y -= 1.5f * _Delta;
		MaskValue.z = MaskValue.y;
	}

	if (MaskValue.y < 0.0f)
	{
		Death();
	}
}
