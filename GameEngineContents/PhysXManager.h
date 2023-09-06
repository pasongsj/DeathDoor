#pragma once
#include "PhysXCustom.h"

// Ό³Έν :
class PhysXManager
{
	friend class PhysXLevel;
	friend class PhysXDefault;
	friend class GameEngineCore;

public:
	// constrcuter destructer
	PhysXManager();
	~PhysXManager();

	static PhysXManager* GetInst()
	{
		static PhysXManager Inst;
		return &Inst;
	}

	// delete Function
	PhysXManager(const PhysXManager& _Other) = delete;
	PhysXManager(PhysXManager&& _Other) noexcept = delete;
	PhysXManager& operator=(const PhysXManager& _Other) = delete;
	PhysXManager& operator=(PhysXManager&& _Other) noexcept = delete;

	

protected:
private:
	physx::PxPhysics* m_pPhysics = nullptr;
	physx::PxScene* m_pScene = nullptr;

	physx::PxFoundation* m_pFoundation = nullptr;
	physx::PxDefaultAllocator m_Allocator;
	class CustomErrorCallback m_ErrorCallback;
	physx::PxPvd* m_pPvd = nullptr;
	physx::PxPvdTransport* m_pTransport = nullptr;
	physx::PxPvdSceneClient* m_pPvdClient = nullptr;

	physx::PxDefaultCpuDispatcher* m_pDispatcher = nullptr;
	class CustomSimulationEventCallback* m_pSimulationEventCallback = nullptr;
	physx::PxCooking* m_pCooking = nullptr;

	std::map<std::string, physx::PxScene*> AllScene;

	void Init();
	void CreateScene(const std::string_view& _Name);
	void ChangeScene(const std::string_view& _Name);

	void Simulate(float _Deltatime);

	void Release();
	


	physx::PxScene* GetScene()
	{
		return m_pScene;
	}

	physx::PxPhysics* GetPhysics()
	{
		return m_pPhysics;
	}

	physx::PxCooking* GetCooking()
	{
		return m_pCooking;
	}

	physx::PxPvdSceneClient* GetPvdClient()
	{
		return m_pPvdClient;
	}

	void SetCameraPvd(float4 _CamPos, float4 _TargetPos)
	{
		float4 CamPos = _CamPos;
		float4 TargetPos = _TargetPos;
		m_pPvdClient->updateCamera("PvdCam", CamPos.PhysXVec3Return(), { 0,1,0 }, TargetPos.PhysXVec3Return());
	}

	bool RayCast(const float4& _vOrigin, const float4& _vDir, OUT float4& _vPoint, float _fDistance = 1000.f);
};

