#include "PrecompileHeader.h"
#include "PhysXControllerComponent.h"

#include <GameEngineBase/GameEngineMath.h>

PhysXControllerComponent::PhysXControllerComponent()
{
}

PhysXControllerComponent::~PhysXControllerComponent()
{
}

void PhysXControllerComponent::CreatePhysXActors(float4 _GeoMetryScale, float4 _GeoMetryRotation)
{
	CreatePhysXActors(_GeoMetryScale.PhysXVec3Return(), _GeoMetryRotation);
}

void PhysXControllerComponent::CreatePhysXActors(physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRotation)
{
	physx::PxVec3 HalfScale = _GeoMetryScale*0.5f;
	HalfScale.x = HalfScale.z;

	m_pPhysics = GetPhysics();
	m_pScene = GetScene();
	physx::PxControllerManager* ControllerManager = PxCreateControllerManager(*m_pScene);
	GetScene()->userData = ControllerManager;
	physx::PxCapsuleControllerDesc  ControllerDesc;
	ControllerDesc.contactOffset = 0.2f;
	ControllerDesc.density = 1.f;
	ControllerDesc.height = static_cast<physx::PxF32>(HalfScale.y - HalfScale.z);
	ControllerDesc.material = m_pPhysics->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fResitution);
	ControllerDesc.radius = static_cast<physx::PxF32>(HalfScale.z );
	ControllerDesc.upDirection = physx::PxVec3(0, 1, 0);
	ControllerDesc.userData = GetActor();
	ControllerDesc.behaviorCallback = NULL;
	ControllerDesc.position = physx::PxExtendedVec3(ParentActor.lock()->GetTransform()->GetWorldPosition().x
													, ParentActor.lock()->GetTransform()->GetWorldPosition().y
													, ParentActor.lock()->GetTransform()->GetWorldPosition().z);
	m_pController = ControllerManager->createController(ControllerDesc);
	
	m_pController->getActor()->getShapes(&m_pShape, sizeof(m_pShape));
	//GetTransform()->SetWorldScale(float4(_GeoMetryScale.x, _GeoMetryScale.y, _GeoMetryScale.z ));
	//GameEngineDebug::DrawCapsule(GetLevel()->GetMainCamera().get(), GetTransform());
}

void PhysXControllerComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	m_pControllerDir = _MoveSpeed;
}


void PhysXControllerComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor = GetActor()->DynamicThis<GameEngineActor>();
}

void PhysXControllerComponent::Update(float _DeltaTime)
{	
	if (m_bGravity)
	{
		m_pController->move(float4(m_pControllerDir.x, m_pControllerDir.y-SCENE_GRAVITY, m_pControllerDir.z).PhysXVec3Return()* _DeltaTime, 0.01f, _DeltaTime, m_pControllerFilter);
	}
	else
	{
		m_pController->move(float4(m_pControllerDir.x, m_pControllerDir.y , m_pControllerDir.z).PhysXVec3Return() * _DeltaTime, 0.01f, _DeltaTime, m_pControllerFilter);
	}
	m_pControllerDir = float4::ZERO;
	float4 tmpWorldPos = { static_cast<float>(m_pController->getPosition().x), static_cast<float>(m_pController->getPosition().y), static_cast<float>(m_pController->getPosition().z) };

	ParentActor.lock()->GetTransform()->SetWorldPosition(tmpWorldPos);

	//if (true == GetLevel()->GetDebugRender())
	//{
	//	GetTransform()->SetWorldRotation(ParentActor.lock()->GetTransform()->GetWorldRotation());
	//	GetTransform()->SetWorldPosition(ParentActor.lock()->GetTransform()->GetWorldPosition());
	//}
}
