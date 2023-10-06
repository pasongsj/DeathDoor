#include "PreCompileHeader.h"
#include "PlayerAttackBomb.h"

#include "ContentFBXRenderer.h"
#include "PhysXSphereComponent.h"

PlayerAttackBomb::PlayerAttackBomb() 
{
}

PlayerAttackBomb::~PlayerAttackBomb() 
{
}

void PlayerAttackBomb::Start()
{
	// Render
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_BOMB_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXSphereComponent>(PLAYER_ATT_BOMB_PHYSX_SCALE);
}

void PlayerAttackBomb::Update(float _DeltaTime)
{
	PlayerAttackBase::Update(_DeltaTime);
}
