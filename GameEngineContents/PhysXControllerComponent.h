#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "PhysXDefault.h"

// Ό³Έν :
class PhysXControllerComponent : public GameEngineComponent, public PhysXDefault
{
public:
	// constrcuter destructer
	PhysXControllerComponent();
	~PhysXControllerComponent();

	// delete Function
	PhysXControllerComponent(const PhysXControllerComponent& _Other) = delete;
	PhysXControllerComponent(PhysXControllerComponent&& _Other) noexcept = delete;
	PhysXControllerComponent& operator=(const PhysXControllerComponent& _Other) = delete;
	PhysXControllerComponent& operator=(PhysXControllerComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRotation = { 0.0f , 0.0f });

	void SetMoveSpeed(float4 _MoveSpeed);

	void SetControllerMoveDir(float4 _Data)
	{
		m_pControllerDir = _Data;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Render() override {}

private:
	physx::PxControllerFilters m_pControllerFilter;
	physx::PxController*  m_pController = nullptr;
	float4 m_pControllerDir = float4::ZERO;
	bool m_bSpeedLimit = false;

	physx::PxVec3 GeoMetryScale;};

