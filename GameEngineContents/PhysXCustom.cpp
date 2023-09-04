#include "PreCompileHeader.h"
#include "PhysXCustom.h"

physx::PxFilterFlags CustomFilterShader
(
	physx::PxFilterObjectAttributes attributes0,
	physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1,
	physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags,
	const void* constantBlock,
	physx::PxU32 constantBlockSize
)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eNOTIFY_TOUCH_FOUND | physx::PxPairFlag::eNOTIFY_TOUCH_LOST | physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT;
		return physx::PxFilterFlag::eDEFAULT;
	}

	// all initial and persisting reports for everything, with per-point data
	pairFlags = physx::PxPairFlag::eSOLVE_CONTACT
		| physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
		| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
		| physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| physx::PxPairFlag::eNOTIFY_TOUCH_LOST
		| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;

	return physx::PxFilterFlag::eDEFAULT;
}

void CustomSimulationEventCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	//트리거에 충돌이 일어났을때 어떤 걸 할 것인지
	while (count--)
	{
		physx::PxTriggerPair& current = *pairs++;

		// 액터가 가지고 있는 쉐이프를 모두 가져옴
		physx::PxRigidActor& tmpOtherActor = *current.otherActor;
		physx::PxFilterData OtherFilterdata = current.otherShape->getSimulationFilterData();
		physx::PxFilterData TriggerFilterdata = current.triggerShape->getSimulationFilterData();
		physx::PxU16 tmpnbShape = current.otherActor->getNbShapes();

		//C26813  : 비트플래그로 사용된 enum끼리의 비교는 == 이 아닌 bitwise and(&)로 비교하는 것이 좋음
		//WARNING : resultFd.word0 == static_cast<physx::PxU32>(PhysXFilterGroup::Ground

		if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle) &&
			TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic) &&
			current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			
			
		}

	}
}


void CustomSimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	// 접촉이 일어났을때 필터를 가져와서 어떻게 처리할것인지

	while (nbPairs--)
	{
		physx::PxContactPair current = *pairs++;
		if (current.contactPatches == 0)
		{
			continue;
		}
		// 액터가 가지고 있는 쉐이프를 모두 가져옴
		physx::PxShape* tmpContactActor = current.shapes[0];
		physx::PxShape* tmpOtherActor = current.shapes[1];
		physx::PxFilterData OtherFilterdata = tmpOtherActor->getSimulationFilterData();
		physx::PxFilterData ContactFilterdata = tmpContactActor->getSimulationFilterData();
		if (ContactFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic)&&// 플레이어
			OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Ground))  //땅			
		{
			
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) //충돌이 시작된 시점
			{
				physx::PxRigidDynamic* pPlayer = static_cast<physx::PxRigidDynamic*>(tmpContactActor->getActor());
				int a = 0;
			}
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS) //충돌이 유지되는동안 계속 들어옴
			{
				int a = 0;
				
			}
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST) //충돌이 끝나는 시점
			{
				int a = 0;
			}
		}
		if (ContactFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic) &&// 플레이어
			OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle))  //장애물		
		{
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) //충돌이 시작된 시점
			{
				int a = 0;
			}
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS) //충돌이 유지되는동안 계속 들어옴
			{
				int a = 0;

			}
			if (current.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST) //충돌이 끝나는 시점
			{
				int a = 0;
			}
		}

	}
}
