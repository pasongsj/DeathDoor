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
	AttackRenderer->SetFBXMesh("ARROW_MESH.fbx", "ContentMeshForward");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_ARROW_RENDER_SCALE);
	AttackRenderer->GetTransform()->SetLocalRotation(PLAYER_ATT_ARROW_RENDER_ROT);
	// PhysX
	CreatePhysXAttComp<PhysXCapsuleComponent>(PLAYER_ATT_ARROW_PHYSX_SCALE, PhysXFilterGroup::PlayerSkill);
	PhysXComp->SetShapeAxis(0,float4::LEFT);
	SetDestTarget(PhysXFilterGroup::MonsterDynamic);

	AttackRenderer->SetColor({ 0.95f, 0.20f, 0.25f }, 5.0f);
	AttackRenderer->GetAllRenderUnit()[0][0]->isLight.X = 0;
	SetAttackAudio("ArrowHit.mp3");
}

void PlayerAttackArrow::Update(float _DeltaTime)
{
	if (true == CheckCollision(PhysXFilterGroup::Obstacle))
	{
		GameEngineSound::Play("ArrowHit.mp3");
		Death();
		return;
	}
	AttackBase::Update(_DeltaTime);
}

