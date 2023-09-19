#include "PrecompileHeader.h"
#include "PhysXControllerComponent.h"

#include <GameEngineBase/GameEngineMath.h>

PhysXControllerComponent::PhysXControllerComponent()
{
}

PhysXControllerComponent::~PhysXControllerComponent()
{
}

void PhysXControllerComponent::CreatePhysXActors(physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRotation)
{
	m_pPhysics = GetPhysics();
	m_pScene = GetScene();
	physx::PxControllerManager* ControllerManager = PxCreateControllerManager(*m_pScene);
	GetScene()->userData = ControllerManager;
	physx::PxCapsuleControllerDesc  ControllerDesc;
	ControllerDesc.contactOffset = 0.2f;
	ControllerDesc.density = 0.01f;
	ControllerDesc.height = static_cast<physx::PxF32>(_GeoMetryScale.y * 0.5f);
	ControllerDesc.material = m_pPhysics->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fResitution);
	ControllerDesc.radius = static_cast<physx::PxF32>(_GeoMetryScale.x * 0.5f);
	ControllerDesc.upDirection = physx::PxVec3(0, 1, 0);
	ControllerDesc.userData = GetActor();
	ControllerDesc.position = physx::PxExtendedVec3(ParentActor.lock()->GetTransform()->GetWorldPosition().x
													, ParentActor.lock()->GetTransform()->GetWorldPosition().y
													, ParentActor.lock()->GetTransform()->GetWorldPosition().z);
	m_pController = ControllerManager->createController(ControllerDesc);
}

void PhysXControllerComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	m_pController->move(_MoveSpeed.PhysXVec3Return(), 1, 0.000001f, m_pControllerFilter);
}


void PhysXControllerComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor = GetActor()->DynamicThis<GameEngineActor>();
}

void PhysXControllerComponent::Update(float _DeltaTime)
{	
	if (m_pControllerDir != float4::ZERO)
	{
		int a = 0;
	}
	m_pController->move(float4(m_pControllerDir.x, m_pControllerDir.y-SCENE_GRAVITY, m_pControllerDir.z).PhysXVec3Return() * _DeltaTime, 1, _DeltaTime, m_pControllerFilter);

	


	float4 tmpWorldPos = { static_cast<float>(m_pController->getPosition().x), static_cast<float>(m_pController->getPosition().y), static_cast<float>(m_pController->getPosition().z) };

	ParentActor.lock()->GetTransform()->SetWorldPosition(tmpWorldPos);
}
