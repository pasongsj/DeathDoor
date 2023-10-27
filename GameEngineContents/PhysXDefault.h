#pragma once
#include "PhysXManager.h"
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnum.h"

enum class SubShapeType
{
	BOX,
	SPHERE,
};

// 설명 : PhysX에서 공통으로 사용할 함수들
class PhysXDefault
{
	typedef struct 
	{
		float x, y, z;
	} vector;

	typedef struct 
	{
		vector i, j, k;
	} matrix;

public:
	// constrcuter destructer
	PhysXDefault();
	~PhysXDefault();

	// delete Function
	PhysXDefault(const PhysXDefault& _Other) = delete;
	PhysXDefault(PhysXDefault&& _Other) noexcept = delete;
	PhysXDefault& operator=(const PhysXDefault& _Other) = delete;
	PhysXDefault& operator=(PhysXDefault&& _Other) noexcept = delete;

	float4 ToEulerAngles(const physx::PxQuat& q);

	//정지마찰계수설정
	inline void SetStaticFriction(float _staticfriction)
	{
		m_fStaticFriction = _staticfriction;
	}
	//운동마찰계수설정
	inline void SetDynamicFriction(float _dynamicfriction)
	{
		m_fDynamicFriction = _dynamicfriction;
	}
	//반발계수설정
	inline void SetRestitution(float _resitution)
	{
		m_fResitution = _resitution;
	}
	//순서대로 정지마찰계수설정, 운동마찰계수설정, 반발계수설정을 넣기
	inline void SetPhysxMaterial(float _staticfriction, float _dynamicfriction, float _resitution)
	{
		m_fStaticFriction = _staticfriction;
		m_fDynamicFriction = _dynamicfriction;
		m_fResitution = _resitution;
	}


	//중력끄기
	virtual void TurnOffGravity() 
	{
		if (m_pRigidDynamic!=nullptr)
		{
			m_bGravity = false;
			m_pRigidDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
		}
	}

	//중력키기
	virtual void TurnOnGravity()
	{
		if (m_pRigidDynamic != nullptr)
		{
			m_bGravity = true;
			m_pRigidDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
		}
	}

	//피벗설정
	inline void SetDynamicPivot(float4 _Pivot)
	{
		m_f4DynamicPivot = _Pivot;
		m_f4DynamicPivot += m_fShapeCenter;
		physx::PxTransform Transform;
		Transform = physx::PxTransform(m_pShape->getLocalPose().q);
		Transform.p = m_f4DynamicPivot.PhysXVec3Return();
		m_pShape->setLocalPose(Transform);
	}	

	inline void SetAggregateObj(bool _Flag)
	{
		m_bAggregateObj = _Flag;
	}

	inline void AddActorAggregate(physx::PxActor* _Actor)
	{
		m_pAggregate->addActor(*_Actor);
	}

	virtual void SetWorldPosWithParent(float4 _Pos, float4 _Rot = float4::ZERONULL);



	float4 GetWorldPosition();

	virtual void SetMoveSpeed(float4 _MoveSpeed) 
	{
		if (m_pRigidDynamic!=nullptr)
		{
			if (true == m_bGravity)
			{
				//Y축은 중력에 의해 가속도를 받지만 X,Z는 가속도를 없애서 정속 이동을 하게끔 함
				m_pRigidDynamic->setLinearVelocity({ 0,m_pRigidDynamic->getLinearVelocity().y,0 });
			}
			else
			{
				m_pRigidDynamic->setLinearVelocity({ 0,0,0 });
			}
			// 캐릭터의 방향을 힘으로 조절
			m_pRigidDynamic->addForce(_MoveSpeed.PhysXVec3Return(), physx::PxForceMode::eVELOCITY_CHANGE);
		}		
	}



	//쿼터니언 관련 함수
	float4 GetQuaternionEulerAngles(float4 rot);
	float4 GetQuaternionEulerAngles(physx::PxQuat rot);
	float4 NormalizeAngles(float4 angles);
	float NormalizeAngle(float angle);
	
	//로드리게스 회전 관련 함수
	float4 RodriguesRotate(vector p, vector v, float a);
	float dotProduct(vector v1, vector v2);
	vector matrixMultiply(matrix m, vector v);

	physx::PxRigidDynamic* GetDynamic()
	{
		return m_pRigidDynamic;
	}

	physx::PxRigidStatic* GetStatic()
	{
		return m_pRigidStatic;
	}

	physx::PxShape* GetShape()
	{
		return m_pShape;
	}
	
	physx::PxPhysics* GetPhysics()
	{
		return PhysXManager::GetInst()->GetPhysics();
	}

	physx::PxScene* GetScene()
	{
		return PhysXManager::GetInst()->GetScene();
	}

	physx::PxCooking* GetCooking()
	{
		return PhysXManager::GetInst()->GetCooking();
	}

	//대상 위치, 쏘는 방향, 차이를 받을 버퍼, 최대사거리
	bool RayCast(const float4& _vOrigin, const float4& _vDir, OUT float4& _vPoint, float _fDistance = 1000.f)
	{
		return PhysXManager::GetInst()->RayCast(_vOrigin, _vDir, _vPoint, _fDistance);
	}

	//false면 레이캐스트에 감지안됨
	void SetRayCastDetect(bool _Value)
	{
		m_pShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, _Value);
	}

	void CreateScene()
	{
		PhysXManager::GetInst()->CreateScene(GameEngineCore::GetCurLevel()->GetName());
	}

	void SetCameraPvd(float4 _CamPos, float4 _TargetPos)
	{
		float4 CamPos = _CamPos;
		float4 TargetPos = _TargetPos;
		PhysXManager::GetInst()->GetPvdClient()->updateCamera("PvdCam", CamPos.PhysXVec3Return(), { 0,1,0 }, TargetPos.PhysXVec3Return());
	}

	void DeathAndRelease();

	void PhysXRelease();

	inline void SetPositionSetFromParentFlag(bool _Flag)
	{
		PositionSetFromParentFlag = _Flag;
		if (nullptr != m_pRigidDynamic)
		{
			m_pRigidDynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, PositionSetFromParentFlag);
		}
	}

	bool IsStatic()
	{
		return m_bStatic;
	}

	virtual void SetFilterData(PhysXFilterGroup _ThisFilter);

	void SetTrigger()
	{
		m_pShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	}

	void SetRigidCollide(bool _Value);


	virtual void CreateSubShape(SubShapeType _Type, float4 _Scale, float4 _LocalPos = float4::ZERO);


	void AttachShape()
	{
		if (m_pRigidDynamic!=nullptr)
		{
			m_pRigidDynamic->attachShape(*m_pSubShape);
			return;
		}

		if (m_pRigidStatic != nullptr)
		{
			m_pRigidStatic->attachShape(*m_pSubShape);
			return;
		}
	}

	void DetachShape()
	{
		if (m_pRigidDynamic != nullptr)
		{
			m_pRigidDynamic->detachShape(*m_pSubShape);
			return;
		}

		if (m_pRigidStatic != nullptr)
		{
			m_pRigidStatic->detachShape(*m_pSubShape);
			return;
		}
	}

	void SetSubShapeFilter(PhysXFilterGroup _ThisFilter)
	{		
		m_pSubShape->setSimulationFilterData
		(
			physx::PxFilterData
			(
				static_cast<physx::PxU32>(_ThisFilter),
				0,
				0,
				0
			)
		);
	}

protected:
	physx::PxController* m_pController = nullptr;
	physx::PxRigidDynamic* m_pRigidDynamic = nullptr;
	physx::PxRigidStatic* m_pRigidStatic = nullptr;
	float m_fStaticFriction = 0.0f;
	float m_fDynamicFriction = 0.0f;
	float m_fResitution = 0.0f;

	float4 m_f4DynamicPivot = float4::ZERO;
	bool m_bAggregateObj = false;
	bool m_bStatic = false;

	bool m_bGravity = true;

	static physx::PxAggregate* m_pAggregate;
	std::weak_ptr<GameEngineActor> ParentActor;

	// Phys액터 생성에 필요한 정보
	physx::PxScene* m_pScene = nullptr;
	physx::PxPhysics* m_pPhysics = nullptr;

	physx::PxMaterial* m_pMaterial = nullptr;
	physx::PxShape* m_pShape = nullptr;
	physx::PxShape* m_pSubShape = nullptr;
	

	float4 m_fShapeCenter = float4::ZERO;
	bool PositionSetFromParentFlag = false;
private:
};

