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
	FireFront = nullptr;
	FireBack = nullptr;

	FireFront = CreateComponent<ContentSpriteRenderer>();
	FireFront->SetMaterial("Fire");
	FireFront->GetShaderResHelper().SetTexture("DiffuseTexture", "FireColor.png");
	FireFront->GetShaderResHelper().SetTexture("NoiseTexture", "FireNoise.png");
	FireFront->GetShaderResHelper().SetTexture("AlphaTexture", "FireAlpha.png");
	FireFront->GetShaderResHelper().SetConstantBufferLink("FireNoise", NoiseData);
	FireFront->GetShaderResHelper().SetConstantBufferLink("DistortionData", DistortionData);

	FireBack = CreateComponent<ContentSpriteRenderer>();
	FireBack->SetMaterial("Fire");
	FireBack->GetShaderResHelper().SetTexture("DiffuseTexture", "FireColor.png");
	FireBack->GetShaderResHelper().SetTexture("NoiseTexture", "FireNoise.png");
	FireBack->GetShaderResHelper().SetTexture("AlphaTexture", "FireAlpha.png");
	FireBack->GetShaderResHelper().SetConstantBufferLink("FireNoise", NoiseData);
	FireBack->GetShaderResHelper().SetConstantBufferLink("DistortionData", DistortionData);
	FireBack->GetTransform()->SetLocalRotation({ 0.0f, 180.0f, 0.0f });

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