#pragma once
#include "PhysXDefault.h"
#include "PhysXCustom.h"

// Ό³Έν :
class PhysXMgr
{
public:
	// constrcuter destructer
	PhysXMgr();
	~PhysXMgr();

	static PhysXMgr* GetInst()
	{
		static PhysXMgr Inst;
		return &Inst;
	}

	// delete Function
	PhysXMgr(const PhysXMgr& _Other) = delete;
	PhysXMgr(PhysXMgr&& _Other) noexcept = delete;
	PhysXMgr& operator=(const PhysXMgr& _Other) = delete;
	PhysXMgr& operator=(PhysXMgr&& _Other) noexcept = delete;

protected:

private:
	physx::PxFoundation* m_pFoundation = nullptr;
	physx::PxDefaultAllocator m_Allocator;
	class CustomErrorCallback m_ErrorCallback;
	physx::PxPvd* m_pPvd = nullptr;

	float m_fStepSize = 0.f;
	float m_fWaitTime = 0.f;

	physx::PxPhysics* m_pPhysics = nullptr;
	physx::PxScene* m_pScene = nullptr;
	physx::PxDefaultCpuDispatcher* m_pDispatcher = nullptr;
	class CustomSimulationEventCallback* m_pSimulationEventCallback = nullptr;
	physx::PxCooking* m_pCooking = nullptr;

	bool advance(physx::PxReal _DeltaTime);
	void Initialize();

	void Simulate(float _Deltatime);

	void Release();

};

