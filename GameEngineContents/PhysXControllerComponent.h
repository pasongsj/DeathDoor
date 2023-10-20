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

	void CreatePhysXActors(float4 _GeoMetryScale = float4(2.0f, 2.0f, 2.0f), float4 _GeoMetryRotation = float4::ZERO);
	void CreatePhysXActors(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f, 2.0f, 2.0f), float4 _GeoMetryRotation = float4::ZERO);

	void SetMoveSpeed(float4 _MoveSpeed);

	inline float4 GetWorldPosition()
	{
		return float4(static_cast<float>(m_pController->getFootPosition().x), static_cast<float>(m_pController->getFootPosition().y), static_cast<float>(m_pController->getFootPosition().z));
	}

	void SetRotation(float4 _Rot)
	{
		ParentActor.lock()->GetTransform()->SetWorldRotation(_Rot);
	}

	void SetWorldPosWithParent(float4 _Pos,float4 _Rot = float4::ZERONULL ) override
	{
		if (_Rot == float4::ZERONULL)
		{
			ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
			m_pController->setFootPosition(physx::PxExtendedVec3(_Pos.x, _Pos.y, _Pos.z));
		}
		else
		{

			ParentActor.lock()->GetTransform()->SetWorldPosition(_Pos);
			ParentActor.lock()->GetTransform()->SetWorldRotation(_Rot);
			m_pController->setFootPosition(physx::PxExtendedVec3(_Pos.x, _Pos.y, _Pos.z));
		}
	}

	void TurnOffGravity() override
	{
		m_bGravity = false;
	}

	void TurnOnGravity() override
	{
		m_bGravity = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Render() override {}

private:
	physx::PxControllerFilters m_pControllerFilter = nullptr;
	float4 m_pControllerDir = float4::ZERO;
	bool m_bSpeedLimit = false;
	bool m_bGravity = true;
	float m_fHeight = 0.f;
	physx::PxVec3 GeoMetryScale;

};

