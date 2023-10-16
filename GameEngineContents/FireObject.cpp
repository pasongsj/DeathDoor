#include "PrecompileHeader.h"
#include "FireObject.h"
#include "ContentSpriteRenderer.h"

FireObject::FireObject()
{
}

FireObject::~FireObject()
{
}

void FireObject::SetRotation(float4 _Rot)
{
	Rot = _Rot;
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


	DistortionData.Distortion1 = { 0.1f, 0.2f };
	DistortionData.Distortion2 = { 0.1f, 0.3f };
	DistortionData.Distortion3 = { 0.1f, 0.1f };
}

void FireObject::Update(float _Delta)
{
	NoiseData.FrameTime += 0.5f * _Delta;

	if (NoiseData.FrameTime >= 10.0f)
	{
		NoiseData.FrameTime -= 10.0f;
	}

	BillBoarding();

	//float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	//float4 FirePos = GetTransform()->GetWorldPosition();
	//
	//CamPos.y = 0.0f;
	//FirePos.y = 0.0f;
	//
	//float4 Dir = CamPos - FirePos;
	//Dir.Normalize();
	//
	//float4 DownLine = { 0.0f, 0.0f, -1.0f };
	//
	//float Radian = DownLine.x * Dir.x + DownLine.y * Dir.y + DownLine.z * Dir.z;
	//float AcosRad = acos(Radian);
	//float Degree = AcosRad * 180 / GameEngineMath::PIE;
	//
	//if (CamPos.x <= FirePos.x)
	//{
	//	GetTransform()->SetWorldRotation({ 0.0f, -90 + Degree, 0.0f });
	//}
	//else
	//{
	//	GetTransform()->SetWorldRotation({ 0.0f, -90 - Degree, 0.0f });
	//}
}

void FireObject::BillBoarding()
{
	float4x4 CamView = GetLevel()->GetMainCamera()->GetView();
	float4 CamForward = GetLevel()->GetMainCamera()->GetTransform()->GetLocalForwardVector();

	float4 BillBoardingAngle = CamForward + Rot;

	GetTransform()->SetWorldRotation(BillBoardingAngle);
}


