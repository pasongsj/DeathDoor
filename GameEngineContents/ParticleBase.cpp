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
	if (isBillBoarding == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCamera> Cam = GetLevel()->GetMainCamera();

	if(Type == BillBoardingType::XYZBillBoarding)
	{
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
		
		Rotation = Rotation.QuaternionToEulerDeg();
		Rotation += RotAngle;

		GetTransform()->SetWorldRotation(Rotation);
	}
	else if(Type == BillBoardingType::XBillBoarding)
	{
		float4 CamDir = Cam->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
		CamDir.Normalize();

		float Dot = CamDir.x * CamDir.x + CamDir.z * CamDir.z;
		float AngleRad = acos(Dot);
		float AngleDeg = AngleRad * GameEngineMath::RadToDeg;

		GetTransform()->SetWorldRotation({ AngleDeg , 0.0f , 0.0f });
	}
}

void ParticleBase::Move(float _Delta)
{
	if (isWorldMove == true)
	{
		GetTransform()->AddWorldPosition(MoveDir * MoveSpeed * _Delta);
	}
	else
	{
		GetTransform()->AddLocalPosition(MoveDir * MoveSpeed * _Delta);
	}
}
