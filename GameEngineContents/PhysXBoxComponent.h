#pragma once

#include <GameEngineCore/GameEngineComponent.h>
#include "PhysXComponent.h"

// 설명 :
class PhysXBoxComponent : public PhysXComponent
{
public:
	// constrcuter destructer
	PhysXBoxComponent();
	~PhysXBoxComponent();

	// delete Function
	PhysXBoxComponent(const PhysXBoxComponent& _Other) = delete;
	PhysXBoxComponent(PhysXBoxComponent&& _Other) noexcept = delete;
	PhysXBoxComponent& operator=(const PhysXBoxComponent& _Other) = delete;
	PhysXBoxComponent& operator=(PhysXBoxComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(float4 _GeoMetryScale = float4(2.0f,2.0f,2.0f), float4 _GeoMetryRot = float4::ZERO, bool _Static = false) override;
	void CreatePhysXActors(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = float4::ZERO,bool _Static = false) override;

	void SetScale(float4 _Scale)
	{
		m_pShape->setGeometry(physx::PxBoxGeometry(_Scale.PhysXVec3Return()));
	}
	void TurnOffSpeedLimit()
	{
		m_bSpeedLimit = false;
	}

	void TurnOnSpeedLimit()
	{
		m_bSpeedLimit = true;
	}

	void SwitchSpeedLimit()
	{
		m_bSpeedLimit = !m_bSpeedLimit;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool m_bSpeedLimit = false;

	//속도제한 함수
	void SpeedLimit();

	void CreateStatic(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = float4::ZERO);
	void CreateDynamic(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = float4::ZERO);
};

