#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXCustom.h"

// Ό³Έν :
class PhysXLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PhysXLevel();
	virtual ~PhysXLevel() = 0;

	// delete Function
	PhysXLevel(const PhysXLevel& _Other) = delete;
	PhysXLevel(PhysXLevel&& _Other) noexcept = delete;
	PhysXLevel& operator=(const PhysXLevel& _Other) = delete;
	PhysXLevel& operator=(PhysXLevel&& _Other) noexcept = delete;

	inline physx::PxScene* GetScene()
	{
		return m_pScene;
	}

	inline physx::PxPhysics* GetPhysics()
	{
		return m_pPhysics;
	}

	inline physx::PxCooking* GetCooking()
	{
		return m_pCooking;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
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

