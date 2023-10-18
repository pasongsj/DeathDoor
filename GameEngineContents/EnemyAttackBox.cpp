#include "PreCompileHeader.h"
#include "EnemyAttackBox.h"
#include "PhysXBoxComponent.h"

EnemyAttackBox::EnemyAttackBox() 
{
}

EnemyAttackBox::~EnemyAttackBox() 
{
}


void EnemyAttackBox::Start()
{
	// PhysX
	CreatePhysXAttComp<PhysXBoxComponent>(float4(300,60,150), PhysXFilterGroup::MonsterSkill);
}

void EnemyAttackBox::Update(float _DeltaTime)
{
	AttackBase::Update(_DeltaTime);
}
