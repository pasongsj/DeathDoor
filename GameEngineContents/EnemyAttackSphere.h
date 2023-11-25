#pragma once
#include "AttackBase.h"

// Ό³Έν :
class EnemyAttackSphere : public AttackBase
{
public:
	// constrcuter destructer
	EnemyAttackSphere();
	~EnemyAttackSphere();

	// delete Function
	EnemyAttackSphere(const EnemyAttackSphere& _Other) = delete;
	EnemyAttackSphere(EnemyAttackSphere&& _Other) noexcept = delete;
	EnemyAttackSphere& operator=(const EnemyAttackSphere& _Other) = delete;
	EnemyAttackSphere& operator=(EnemyAttackSphere&& _Other) noexcept = delete;

	void SetRender(const float4& _RenderScale, const std::string_view& _Mesh = "");
	void SetPhysXComp(const float4& _PhysXScale, const float4& _Pivot = float4::ZERO);

	void SetShoot(float _Speed) override
	{
		AttackBase::SetShoot(_Speed);
	}

	void SetDustColor(const float4& _Color)
	{
		DustColor = _Color;
	}



protected:
	void Update(float _DeltaTime) override;
	void CreateParticle(float _DeltaTime);

private:
	float ParticleCount = 0.0f;
	float4 DustColor = float4::ZERONULL;

};

