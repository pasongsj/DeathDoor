#include "PreCompileHeader.h"
#include "PlayerAttackArrow.h"

#include "ContentFBXRenderer.h"
#include "PhysXCapsuleComponent.h"

PlayerAttackArrow::PlayerAttackArrow()
{
}

PlayerAttackArrow::~PlayerAttackArrow()
{
}

void PlayerAttackArrow::Start()
{
	// Render
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_ARROW_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXCapsuleComponent>(PLAYER_ATT_ARROW_PHYSX_SCALE);
}

void PlayerAttackArrow::Update(float _DeltaTime)
{
	PlayerAttackBase::Update(_DeltaTime);
}

