#include "PreCompileHeader.h"
#include "PlayerAttackBasic.h"
#include "PhysXBoxComponent.h"

PlayerAttackBasic::PlayerAttackBasic()
{
}

PlayerAttackBasic::~PlayerAttackBasic()
{
}

void PlayerAttackBasic::Start()
{
	// Attack Box
	CreatePhysXAttComp<PhysXBoxComponent>(PLAYER_ATT_BOX_PHYSX_SCALE, PhysXFilterGroup::PlayerSkill);

}
