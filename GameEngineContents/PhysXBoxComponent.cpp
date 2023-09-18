#include "PreCompileHeader.h"
#include "PhysXBoxComponent.h"

#include <GameEngineCore/GameEngineActor.h>

PhysXBoxComponent::PhysXBoxComponent()
{
}

PhysXBoxComponent::~PhysXBoxComponent()
{
}

void PhysXBoxComponent::CreatePhysXActors(physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot, bool _Static)
{
	m_bStatic = _Static;
	if (true == m_bStatic)
	{
		CreateStatic(_GeoMetryScale, _GeoMetryRot);
	}
	else
	{
		CreateDynamic(_GeoMetryScale, _GeoMetryRot);
	}
}

void PhysXBoxComponent::CreateStatic(physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.EulerDegToQuaternion();
	m_pPhysics = GetPhysics();
	m_pScene = GetScene();
	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm
	(
		physx::PxVec3
		(
			ParentActor.lock()->GetTransform()->GetWorldPosition().x
			, ParentActor.lock()->GetTransform()->GetWorldPosition().y
			, ParentActor.lock()->GetTransform()->GetWorldPosition().z
		),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w)
	);

	// Staticfriction : 정적마찰 // Dynamicfriction : 동적마찰 // Resitution : 탄성계수
	m_pMaterial = m_pPhysics->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fResitution);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale
	(
		_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f
	);

	// 충돌체의 종류
	m_pRigidStatic = m_pPhysics->createRigidStatic(localTm);

	// 중력이 적용되지 않도록
	// TODO::RigidStatic으로 변경해야
	m_pRigidStatic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	m_pShape = physx::PxRigidActorExt::createExclusiveShape(*m_pRigidStatic, physx::PxBoxGeometry(tmpGeoMetryScale), *m_pMaterial);


	//피벗 설정
	physx::PxVec3 Pivot(m_f4DynamicPivot.x, m_f4DynamicPivot.y, m_f4DynamicPivot.z);
	m_pShape->setLocalPose(physx::PxTransform(Pivot));		

	//충돌할때 필요한 필터 데이터
	m_pShape->setSimulationFilterData
	(
		physx::PxFilterData
		(
			static_cast<physx::PxU32>(PhysXFilterGroup::None),
			0,
			0,
			0
		)
	);

	m_pShape->userData = GetActor();
	// Scene에 액터 추가
	if (true == m_bAggregateObj)
	{
		AddActorAggregate(m_pRigidStatic);
	}
	else
	{
		m_pScene->addActor(*m_pRigidStatic);
	}
}

void PhysXBoxComponent::CreateDynamic(physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.EulerDegToQuaternion();
	m_pPhysics = GetPhysics();
	m_pScene = GetScene();
	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm
	(
		physx::PxVec3
		(
			ParentActor.lock()->GetTransform()->GetWorldPosition().x
			, ParentActor.lock()->GetTransform()->GetWorldPosition().y
			, ParentActor.lock()->GetTransform()->GetWorldPosition().z
		),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w)
	);

	// Staticfriction : 정적마찰 // Dynamicfriction : 동적마찰 // Resitution : 탄성계수
	m_pMaterial = m_pPhysics->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fResitution);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale
	(
		_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f
	);

	// 충돌체의 종류
	m_pRigidDynamic = m_pPhysics->createRigidDynamic(localTm);

	// 중력이 적용되지 않도록
	// TODO::RigidStatic으로 변경해야
	//m_pRigidDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
	//m_pRigidDynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	m_pShape = physx::PxRigidActorExt::createExclusiveShape(*m_pRigidDynamic, physx::PxBoxGeometry(tmpGeoMetryScale), *m_pMaterial);

	// RigidDynamic의 밀도를 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*m_pRigidDynamic, 0.1f);

	//피벗 설정
	physx::PxVec3 Pivot(m_f4DynamicPivot.x, m_f4DynamicPivot.y, m_f4DynamicPivot.z);
	m_pShape->setLocalPose(physx::PxTransform(Pivot));


	///////////////////////////
	//m_pShape->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Ground),
	//	static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic), 0, 0));
	///////////////////////////


	

	//콜백피벗 설정
	m_pShape->setLocalPose(physx::PxTransform(Pivot));

	m_pShape->userData = GetActor();
	// Scene에 액터 추가
	if (true == m_bAggregateObj)
	{
		AddActorAggregate(m_pRigidDynamic);
	}
	else
	{
		m_pScene->addActor(*m_pRigidDynamic);
	}
}

void PhysXBoxComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor = GetActor()->DynamicThis<GameEngineActor>();
}

void PhysXBoxComponent::Update(float _DeltaTime)
{	
	if (true == IsStatic())
	{
		if (true == PositionSetFromParentFlag)
		{
			float4 tmpQuat = ParentActor.lock()->GetTransform()->GetWorldRotation().EulerDegToQuaternion();

			physx::PxTransform tmpPxTransform
			(
				ParentActor.lock()->GetTransform()->GetWorldPosition().x,
				ParentActor.lock()->GetTransform()->GetWorldPosition().y,
				ParentActor.lock()->GetTransform()->GetWorldPosition().z,
				physx::PxQuat
				(
					tmpQuat.x,
					tmpQuat.y,
					tmpQuat.z,
					tmpQuat.w
				)
			);

			// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
			m_pRigidStatic->setGlobalPose(tmpPxTransform);
			// TODO::회전도 처리해야함. DegreeToQuat
		}
	}
	else
	{
		if (true == PositionSetFromParentFlag)
		{
			float4 tmpQuat = ParentActor.lock()->GetTransform()->GetWorldRotation().EulerDegToQuaternion();

			physx::PxTransform tmpPxTransform
			(
				ParentActor.lock()->GetTransform()->GetWorldPosition().x,
				ParentActor.lock()->GetTransform()->GetWorldPosition().y,
				ParentActor.lock()->GetTransform()->GetWorldPosition().z,
				physx::PxQuat
				(
					tmpQuat.x,
					tmpQuat.y,
					tmpQuat.z,
					tmpQuat.w
				)
			);

			// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
			m_pRigidDynamic->setGlobalPose(tmpPxTransform);
			// TODO::회전도 처리해야함. DegreeToQuat
			return;
		}
		// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
		float4 tmpWorldPos = { m_pRigidDynamic->getGlobalPose().p.x, m_pRigidDynamic->getGlobalPose().p.y, m_pRigidDynamic->getGlobalPose().p.z };
		float4 EulerRot = PhysXDefault::GetQuaternionEulerAngles(m_pRigidDynamic->getGlobalPose().q) * GameEngineMath::RadToDeg;

		ParentActor.lock()->GetTransform()->SetWorldRotation(float4{ EulerRot.x, EulerRot.y, EulerRot.z });
		ParentActor.lock()->GetTransform()->SetWorldPosition(tmpWorldPos);

		if (m_bSpeedLimit == true)
		{
			SpeedLimit();
		}
	}
}

void PhysXBoxComponent::SpeedLimit()
{
	physx::PxVec3 Velo = m_pRigidDynamic->getLinearVelocity();
	physx::PxVec2 Velo2D(Velo.x, Velo.z);

	if (Velo2D.magnitude() > PLAYER_MAX_SPEED)
	{
		Velo2D.normalize();
		Velo2D *= PLAYER_MAX_SPEED;
		Velo.x = Velo2D.x;
		Velo.z = Velo2D.y;

		m_pRigidDynamic->setLinearVelocity(Velo);
	}
}
