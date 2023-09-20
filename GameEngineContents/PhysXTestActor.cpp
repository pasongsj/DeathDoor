#include "PrecompileHeader.h"
#include "PhysXTestActor.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXConvexComponent.h"
#include "PhysXTriangleComponent.h"
#include "PhysXSphereComponent.h"

#include "PhysXTestLevel.h"
#include "MapTestLevel.h"

PhysXTestActor::PhysXTestActor() 
{
}

PhysXTestActor::~PhysXTestActor() 
{
}

void PhysXTestActor::Start()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Player.fbx", "MeshAniTextureDeferred");
	m_pRenderer->GetTransform()->SetLocalScale(m_pRenderer->GetTransform()->GetLocalScale() * 100.f);

	// 스케일은 렌더유닛0번의 boundScale 혹은 모든 유닛돌면서 boundscale가져오는 해당함수 사용(임의지정해도됨 상관없음)
	float4 scale = m_pRenderer->GetMeshScale() * 100.f;


	m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>(); // 원하는 모양의 PhysXComponent부착

	m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);			//앞에서부터 정지마찰, 운동마찰, 반발력계수 세팅

	m_pCapsuleComp->CreatePhysXActors(scale.PhysXVec3Return()); // 피직스 액터를 만드는 부분. 크기는 설정안하면 기본값 세팅됨

	m_pCapsuleComp->TurnOnSpeedLimit();							//최대 이동속도 제한하는 함수
	m_pCapsuleComp->GetDynamic()->setMass(65.f);				// 무게 설정 조정이 아직 필요한듯함

	// PS. float4에 PhysX 관련함수 만들어뒀음 PxVec3 혹은 PxQuat(쿼터니온) 으로 쉽게 변환 가능함
}

void PhysXTestActor::Update(float _DeltaTime)
{
	float4 ResultPoint = float4::ZERO;
	m_pCapsuleComp->RayCast(this->GetTransform()->GetWorldPosition(), float4::DOWN, ResultPoint);
	
	float4 Movedir = float4::ZERO;
	if (true == GameEngineInput::IsPress("CamMoveLeft"))
	{
		Movedir += GetTransform()->GetWorldLeftVector() * 500.f * _DeltaTime;
		//GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveRight"))
	{
		Movedir += GetTransform()->GetWorldRightVector() * 500.f * _DeltaTime;
		//GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsDown("CamMoveUp"))
	{
		Movedir += GetTransform()->GetWorldUpVector() * 500.f * _DeltaTime;
		m_pCapsuleComp->SetMoveJump();
	}
	if (true == GameEngineInput::IsPress("CamMoveDown"))
	{
		Movedir += GetTransform()->GetWorldDownVector() * 500.f * _DeltaTime;
		//GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveForward"))
	{
		Movedir += GetTransform()->GetWorldForwardVector() * 500.f * _DeltaTime;
		//GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveBack"))
	{
		Movedir += GetTransform()->GetWorldBackVector() * 500.f * _DeltaTime;
		//GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * 500.f * _DeltaTime);
	}
	Movedir.Normalize();
	//physx::PxTransform test= float4::PhysXTransformReturn(GetTransform()->GetWorldRotation(), Movedir * 1000.f * _DeltaTime);
	//physx::PxTransform test2 = m_pSphereComp->GetDynamic()->getGlobalPose();
	//test.p += test2.p;
	//m_pSphereComp->GetDynamic()->setGlobalPose(test);
	m_pCapsuleComp->SetMoveSpeed(Movedir * PLAYER_MAX_SPEED*2.f);
}