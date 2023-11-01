#pragma once

physx::PxFilterFlags CustomFilterShader
(
	physx::PxFilterObjectAttributes attributes0,
	physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1,
	physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags,
	const void* constantBlock,
	physx::PxU32 constantBlockSize
);

// callback 이벤트를 재정의할 클래스
class CustomSimulationEventCallback : public physx::PxSimulationEventCallback
{
public:
	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
	void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {};
	void onWake(physx::PxActor** actors, physx::PxU32 count) override {};
	void onSleep(physx::PxActor** actors, physx::PxU32 count) override {};
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
	void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {};

private:
	
};


class CustomErrorCallback : public physx::PxErrorCallback
{
private:
	void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
	{
		std::string Code = "Code : " + std::to_string(code)
			+ "\nMsg : " + message
			+ "\nFile : " + file
			+ "\nLine : " + std::to_string(line);
		if (code == 2)
		{
			return;
		}
		MsgAssert(Code);
	}
};


class CustomQueryFilterCallback : public physx::PxQueryFilterCallback
{
	friend class PhysXControllerComponent;
private:
	physx::PxQueryHitType::Enum preFilter(
		const physx::PxFilterData& filterData, const physx::PxShape* shape, const physx::PxRigidActor* actor, physx::PxHitFlags& queryFlags) override;

private:
};
class CustomCctBehaviorCallback : public physx::PxControllerBehaviorCallback
{
	friend class PhysXControllerComponent;
	physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) override;

	physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxController& controller) override
	{
		return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT;
	}

	physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxObstacle& obstacle)  override
	{
		return physx::PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT;
	}

	void SetOwner(std::shared_ptr<class PhysXControllerComponent> _OwnerComp)
	{
		m_pOwnerComp = _OwnerComp;
	}

private:
	
	std::weak_ptr<class PhysXControllerComponent> m_pOwnerComp;

};

class CustomCctFilterCallback : public physx::PxControllerFilterCallback
{
	friend class PhysXControllerComponent;
public:
	bool filter(const physx::PxController& a, const physx::PxController& b) override
	{
		return m_bReturnValue;
	}
	void SetRigid(bool _Value)
	{
		m_bReturnValue = _Value;
	}
private:
	bool m_bReturnValue;
};