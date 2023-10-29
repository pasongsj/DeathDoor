#include "PrecompileHeader.h"
#include "DustParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

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

	//GetUnit()->ShaderResHelper.SetTexture("DiffuseTexture", "DustParticleNoise.png");
	GetUnit()->ShaderResHelper.SetTexture("NoiseTexture1", "ParticleNoise1.png");
	GetUnit()->ShaderResHelper.SetTexture("NoiseTexture2", "ParticleNoise2.png");
	GetUnit()->ShaderResHelper.SetTexture("AlphaTexture", "ParticleAlpha.png");

	GetUnit()->ShaderResHelper.SetConstantBufferLink("MaskValue", MaskValue);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("DistortionData", Distortion);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("DiffuseUV", DiffuseUV);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("BlurColor", BlurColor);

	float Distortion1 = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);
	float Distortion2 = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);

	float DistortionScale = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);
	float DistortionBias = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);

	Distortion.Distortion = float4{ Distortion1 ,Distortion1 ,Distortion2, Distortion2 };

	Distortion.DistortionScale = DistortionScale;
	Distortion.DistortionBias = DistortionBias;

	GetTransform()->SetLocalScale({ 5.0f, 5.0f, 1.0f });

	SetAngle({ 55.0f, 0.0f, 0.0f });
	
	SetColor();

	//float DiffuseUVX = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	//float DiffuseUVY = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	//
	//DiffuseUV.x += DiffuseUVX;
	//DiffuseUV.y += DiffuseUVY;

}

void DustParticle::Update(float _Delta)
{
	BillBoarding();

	FadeInAndOut(_Delta);

}

void DustParticle::Render(float _Delta)
{
}

void DustParticle::SetColor(float4 _RGBA)
{
	GetUnit()->Color.PlusColor = _RGBA;
}

void DustParticle::SetGlow(float4 _GlowColor)
{
	if (_GlowColor == float4::ZERO)
	{
		BlurColor = GetUnit()->Color.PlusColor;
		return;
	}

	BlurColor = _GlowColor;
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
		Death();
	}
}
