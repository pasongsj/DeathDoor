#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXCustom.h"

// 설명 :
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

	void CreateScene()
	{
		PhysXManager::GetInst()->CreateScene(GetName());
	}

	void SetCameraPvd(float4 _CamPos, float4 _TargetPos)
	{
		float4 CamPos = _CamPos;
		float4 TargetPos = _TargetPos;
		PhysXManager::GetInst()->GetPvdClient()->updateCamera("PvdCam", CamPos.PhysXVec3Return(), { 0,1,0 }, TargetPos.PhysXVec3Return());
	}

	/// <summary>
	/// RayCast
	/// </summary>
	/// <param name="_vOrigin"></param> 현재 위치
	/// <param name="_vDir"></param> 쏘는 방향
	/// <param name="_vPoint"></param> 결과위치
	/// <param name="_fDistance"></param> 체크거리
	/// <returns></returns>
	bool RayCast(const float4& _vOrigin, const float4& _vDir, OUT float4& _vPoint, float _fDistance = 1000.f)
	{
		return PhysXManager::GetInst()->RayCast(_vOrigin, _vDir, _vPoint, _fDistance);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

};

