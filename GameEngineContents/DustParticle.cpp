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
	GetUnit()->SetMaterial("DustParticle", RenderPath::Alpha);

	//GetUnit()->ShaderResHelper.SetTexture("DiffuseTexture", "DustParticleNoise.png");
	GetUnit()->ShaderResHelper.SetTexture("NoiseTexture1", "ParticleNoise.png");
	GetUnit()->ShaderResHelper.SetTexture("AlphaTexture", "ParticleAlpha.png");

	GetUnit()->ShaderResHelper.SetConstantBufferLink("MaskValue", MaskValue);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("DistortionData", Distortion);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("DiffuseUV", DiffuseUV);
	GetUnit()->ShaderResHelper.SetConstantBufferLink("BlurColor", BlurColor);

	float Distortion1 = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.4f);
	float Distortion2 = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.4f);

	float DistortionScale = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.4f);
	float DistortionBias = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.4f);

	Distortion.Distortion = float4{ Distortion1 ,Distortion1 ,Distortion2, Distortion2 };

	Distortion.DistortionScale = DistortionScale;
	Distortion.DistortionBias = DistortionBias;

	float DirX = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);
	float DirY = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);

	Dir = { DirX, DirY };
	Dir.Normalize();
	SetBillBoardingType(BillBoardingType::XBillBoarding);

	GetTransform()->SetLocalScale({ 5.0f, 5.0f, 1.0f });
	
	SetColor();
}

void DustParticle::Update(float _Delta)
{
	DiffuseUV.x += Dir.x * _Delta;
	DiffuseUV.y += Dir.y * _Delta;

	BillBoarding();
	
	Move(_Delta);

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_Delta);
	}
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

void DustParticle::FadeLoop(float _Delta)
{
	LoopAngle += 540.0f * _Delta;
	float LadLoopAngle = LoopAngle * GameEngineMath::DegToRad;

	MaskValue.x = (sin(LadLoopAngle) / 4.0f) + 0.75f;
	MaskValue.z = MaskValue.x;
}


void DustParticle::FadeInAndOut(float _Delta)
{
	if (MaskValue.x < 1.0f)
	{
		MaskValue.x += FadeSpeed * _Delta;
		MaskValue.z = MaskValue.x;
	}
	else if(MaskValue.y > 0.0f)
	{
		MaskValue.y -= FadeSpeed * _Delta;
		MaskValue.z = MaskValue.y;
	}
	else if (MaskValue.y <= 0.0f)
	{
		Death();
	}
}

void DustParticle::FadeIn(float _Delta)
{
	if (MaskValue.x <= 1.0f)
	{
	MaskValue.x += FadeSpeed * _Delta;
	MaskValue.z = MaskValue.y;
	}
	else
	{
		Death();
	}
}

void DustParticle::FadeOut(float _Delta)
{
	if (MaskValue.x >= 0.0f)
	{
		MaskValue.x -= FadeSpeed * _Delta;
		MaskValue.z = MaskValue.x;
	}
	else
	{
		Death();
	}
}
