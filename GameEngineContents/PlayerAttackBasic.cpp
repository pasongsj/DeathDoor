#include "PreCompileHeader.h"
#include "PlayerAttackBasic.h"
#include "PhysXBoxComponent.h"

PlayerAttackBasic::PlayerAttackBasic()
{
}

PlayerAttackBasic::~PlayerAttackBasic()
{
}

float SizeofBox = 200.0f;
void PlayerAttackBasic::Start()
{
	// Attack Box
	float4 BoxScale = float4{ SizeofBox,1.0f,SizeofBox };
	CreatePhysXAttComp<PhysXBoxComponent>(BoxScale);

}
