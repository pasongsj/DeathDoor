#include "PreCompileHeader.h"
#include "PlayerAttackMagic.h"

#include "ContentFBXRenderer.h"
#include "PhysXSphereComponent.h"

#include "DustParticle.h"

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
	CreatePhysXAttComp<PhysXSphereComponent>(PLAYER_ATT_MAGIC_PHYSX_SCALE, PhysXFilterGroup::PlayerSkill);
	SetDestTarget(PhysXFilterGroup::MonsterDynamic);

	AttackRenderer->SetGlowToUnit(0, 0);
	AttackRenderer->SetColor({ 233.0f / 255.0f, 77.0f / 255.0f, 0.1f }, 4.0f);
}

void PlayerAttackMagic::Update(float _DeltaTime)
{
	AttackBase::Update(_DeltaTime);
	CreateParticle(_DeltaTime);
}

void PlayerAttackMagic::CreateParticle(float _DeltaTime)
{
	ParticleCount += _DeltaTime;

	if (ParticleCount >= 0.01f)
	{
		ParticleCount = 0.0f;

		std::shared_ptr<DustParticle> NewParticle = CreateComponent<DustParticle>();
		NewParticle->SetColor({ 233.0f / 255.0f, 77.0f / 255.0f });
		NewParticle->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		NewParticle->GetTransform()->SetLocalScale({ 50.0f, 50.0f, 50.0f });
		NewParticle->SetGlow();
		NewParticle->SetWorldMove();
		NewParticle->SetFadeOut(true);
	}
}
