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

	//BillBoarding();
}

void FireObject::BillBoarding()
{
	std::shared_ptr<GameEngineCamera> Cam = GetLevel()->GetMainCamera();
	float4 CamRot = Cam->GetTransform()->GetWorldRotation();
	float4x4 CamRotMatrix = CamRot.QuaternionToRotationMatrix();
	
	float4x4 RotMatrix;
	RotMatrix.Identity();
	
	RotMatrix.Arr2D[0][0] = CamRotMatrix.Arr2D[0][0];
	RotMatrix.Arr2D[0][2] = CamRotMatrix.Arr2D[0][2];
	RotMatrix.Arr2D[2][0] = CamRotMatrix.Arr2D[2][0];
	RotMatrix.Arr2D[2][2] = CamRotMatrix.Arr2D[2][2];
	
	float4 Rotation = float4::ZERO;
	Rotation = Rotation.MatrixToQuaternion(CamRotMatrix.InverseReturn());
	Rotation += Rot;
	
	GetTransform()->SetWorldRotation(Rotation);
}


