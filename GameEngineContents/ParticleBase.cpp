#include "PrecompileHeader.h"
#include "ParticleBase.h"

#include <GameEngineCore/GameEngineLevel.h>

ParticleBase::ParticleBase()
{
}

ParticleBase::~ParticleBase()
{
}

void ParticleBase::Start()
{
	PushCameraRender(0);
	
	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
}

void ParticleBase::Update(float _Delta)
{

}

void ParticleBase::Render(float _Delta)
{

}

void ParticleBase::SetAngle(float4 _RotAngle)
{
	RotAngle = _RotAngle;
}

void ParticleBase::BillBoarding()
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
	Rotation += RotAngle;

	//ÀÌ°Íµµ µÊ.
	//float4 Dir = GetTransform()->GetWorldPosition() - Cam->GetTransform()->GetWorldPosition();
	//Dir.Normalize();
	//
	//DirectX::XMMATRIX RotTest = DirectX::XMMatrixLookAtLH(Dir, Cam->GetTransform()->GetWorldUpVector(), float4::Cross3DReturn(Cam->GetTransform()->GetWorldUpVector(), Dir));
	//float4 RotQT = DirectX::XMQuaternionRotationMatrix(RotTest);

	GetTransform()->SetWorldRotation(Rotation);
}
