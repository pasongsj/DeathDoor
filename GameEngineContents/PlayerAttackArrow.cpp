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
	AttackRenderer->SetFBXMesh("ARROW_MESH.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_ARROW_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXCapsuleComponent>(PLAYER_ATT_ARROW_PHYSX_SCALE);
	PhysXComp->SetShapeAxis(0,float4::LEFT);
	AttackRenderer->GetTransform()->SetLocalScale(float4{1.0f,0.5f,1.0f});
	AttackRenderer->GetTransform()->SetLocalRotation(float4{ 0.0f,-15.0f,-90.0f });
}

void PlayerAttackArrow::Update(float _DeltaTime)
{
	if (IsShoot() == true)
	{
		AttackRenderer->GetTransform()->SetLocalRotation(float4{ 0.0f,-0.0f,-90.0f });
	}
	PlayerAttackBase::Update(_DeltaTime);
}

