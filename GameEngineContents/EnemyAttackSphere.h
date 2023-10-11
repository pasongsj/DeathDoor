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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

