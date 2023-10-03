#include "PreCompileHeader.h"
#include "PlayerAttackRange.h"
#include "PhysXBoxComponent.h"
#include "Player.h"

PlayerAttackRange::PlayerAttackRange()
{
}

PlayerAttackRange::~PlayerAttackRange()
{
}

float SizeofBox = 200.0f;
void PlayerAttackRange::Start()
{
	{ // Attack Box
		float4 BoxScale = float4{ SizeofBox,1.0f,SizeofBox };
		AttackBoxComponent = CreateComponent<PhysXBoxComponent>();
		AttackBoxComponent->SetPhysxMaterial(1.f, 1.f, 0.f);
		AttackBoxComponent->CreatePhysXActors(BoxScale, float4::ZERO);
		AttackBoxComponent->SetTrigger();
		if (nullptr == Player::MainPlayer)
		{
			return;
		}
		GameEngineTransform* Trans = Player::MainPlayer->GetTransform();
		AttackBoxComponent->SetWorldPosWithParent(Trans->GetWorldPosition() + Trans->GetWorldBackVector() * SizeofBox + float4{0.0f,50.0f,0.0f});
		AttackBoxComponent->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
		//AttackBoxComponent->

	}
}

void PlayerAttackRange::Update(float _DeltaTime)
{
	GameEngineTransform* Trans = Player::MainPlayer->GetTransform();
	AttackBoxComponent->SetWorldPosWithParent(Trans->GetWorldPosition() + Trans->GetWorldBackVector() * SizeofBox + float4{ 0.0f,50.0f,0.0f });
}
