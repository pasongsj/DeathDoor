#include "PreCompileHeader.h"
#include "PlayerAttackMagic.h"

#include "ContentFBXRenderer.h"
#include "PhysXSphereComponent.h"

PlayerAttackMagic::PlayerAttackMagic()
{
}

PlayerAttackMagic::~PlayerAttackMagic()
{
}



void PlayerAttackMagic::Start()
{
	// Render
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_MAGIC_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXSphereComponent>(PLAYER_ATT_MAGIC_PHYSX_SCALE);
}

void PlayerAttackMagic::Update(float _DeltaTime)
{
	PlayerAttackBase::Update(_DeltaTime);
}
