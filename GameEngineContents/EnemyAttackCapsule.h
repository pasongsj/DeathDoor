#pragma once
#include "AttackBase.h"
#include "PhysXCapsuleComponent.h"

// Ό³Έν :
class EnemyAttackCapsule : public AttackBase
{
public:
	// constrcuter destructer
	EnemyAttackCapsule();
	~EnemyAttackCapsule();

	// delete Function
	EnemyAttackCapsule(const EnemyAttackCapsule& _Other) = delete;
	EnemyAttackCapsule(EnemyAttackCapsule&& _Other) noexcept = delete;
	EnemyAttackCapsule& operator=(const EnemyAttackCapsule& _Other) = delete;
	EnemyAttackCapsule& operator=(EnemyAttackCapsule&& _Other) noexcept = delete;

	void SetRender(const float4& _RenderScale, const float4& _RenderRotate = float4::ZERO , std::string_view _Mesh = "");

	void SetPhysXComp(const float4& _PhysXScale, const float4& _Pivot = float4::ZERO, const float4& _Axis = float4::UP);

	void SetShoot(float _Speed) override
	{
		AttackBase::SetShoot(_Speed);
	}

protected:
	void Update(float _DeltaTime) override;
private:

};

