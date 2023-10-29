#pragma once
#include "AttackBase.h"
#include "PhysXBoxComponent.h"

// Ό³Έν :
class EnemyAttackBox : public AttackBase
{
public:
	// constrcuter destructer
	EnemyAttackBox();
	~EnemyAttackBox();

	// delete Function
	EnemyAttackBox(const EnemyAttackBox& _Other) = delete;
	EnemyAttackBox(EnemyAttackBox&& _Other) noexcept = delete;
	EnemyAttackBox& operator=(const EnemyAttackBox& _Other) = delete;
	EnemyAttackBox& operator=(EnemyAttackBox&& _Other) noexcept = delete;

	void SetScale(float4 _Scale)
	{
		PhysXBoxComponent* pBoxComp = reinterpret_cast<PhysXBoxComponent*>(PhysXComp.get());
		pBoxComp->SetScale(_Scale);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

