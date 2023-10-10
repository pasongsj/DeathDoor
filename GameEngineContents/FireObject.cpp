#include "PrecompileHeader.h"
#include "FireObject.h"
#include "ContentSpriteRenderer.h"

FireObject::FireObject()
{
}

FireObject::~FireObject()
{
}

void FireObject::Start()
{
	FireRender = nullptr;

	FireRender = CreateComponent<ContentSpriteRenderer>();
	FireRender->SetMesh("CYLINDER");
	FireRender->SetMaterial("Fire");
	FireRender->GetShaderResHelper().SetTexture("DiffuseTexture", "FireColor.png");
	FireRender->GetShaderResHelper().SetTexture("NoiseTexture", "FireNoise.png");
	FireRender->GetShaderResHelper().SetTexture("AlphaTexture", "FireAlpha.png");
	FireRender->GetShaderResHelper().SetConstantBufferLink("FireNoise", NoiseData);
	FireRender->GetShaderResHelper().SetConstantBufferLink("DistortionData", DistortionData);

	GetTransform()->SetLocalRotation({ 0.0f, -90.0f, 0.0f });

	DistortionData.Distortion1 = { 0.1f, 0.2f };
	DistortionData.Distortion2 = { 0.1f, 0.3f };
	DistortionData.Distortion3 = { 0.1f, 0.1f };
}

void FireObject::Update(float _Delta)
{
	NoiseData.FrameTime += _Delta;

	if (NoiseData.FrameTime >= 10.0f)
	{
		NoiseData.FrameTime -= 10.0f;
	}
}


