#include "PreCompileHeader.h"
#include "EnemyAttackSphere.h"
#include "PhysXSphereComponent.h"
#include "DustParticle.h"

EnemyAttackSphere::EnemyAttackSphere()
{
}

EnemyAttackSphere::~EnemyAttackSphere()
{
}



void EnemyAttackSphere::SetRender(const float4& _RenderScale, const std::string_view& _Mesh)
{
	// Render
	if (nullptr == AttackRenderer)
	{
		AttackRenderer = CreateComponent< ContentFBXRenderer>();
	}
	if ("" == _Mesh)
	{
		AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	}
	else
	{
		AttackRenderer->SetFBXMesh(_Mesh.data(), "ContentMeshDeffered");

	}
	AttackRenderer->GetTransform()->SetLocalScale(_RenderScale);
}

void EnemyAttackSphere::SetPhysXComp(const float4& _PhysXScale, const float4& _Pivot)
{
	// PhysX
	CreatePhysXAttComp<PhysXSphereComponent>(_PhysXScale, PhysXFilterGroup::MonsterSkill);
	PhysXComp->SetDynamicPivot(_Pivot);
	SetDestTarget(PhysXFilterGroup::PlayerDynamic);

}

void EnemyAttackSphere::Update(float _DeltaTime)
{
	if (CheckCollision(PhysXFilterGroup::Ground)|| CheckCollision(PhysXFilterGroup::Obstacle))
	{
		if ("" != AttackEndSound)
		{
			GameEngineSoundPlayer EndSound = GameEngineSound::Play(AttackEndSound);
			EndSound.SetVolume(0.5f);

		}
		Death();
		return;
	}

	if (GetLiveTime() > GetFireTime() + 3.f)
	{
		Death();
		return;
	}

	AttackBase::Update(_DeltaTime);
	if (DustColor != float4::ZERONULL)
	{
		CreateParticle(_DeltaTime);
	}
}

void EnemyAttackSphere::CreateParticle(float _DeltaTime)
{
	ParticleCount += _DeltaTime;

	if (ParticleCount >= 0.01f)
	{
		ParticleCount = 0.0f;

		std::shared_ptr<DustParticle> NewParticle = CreateComponent<DustParticle>();
		NewParticle->SetColor(DustColor);
		NewParticle->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		NewParticle->GetTransform()->SetLocalScale({ 50.0f, 50.0f, 50.0f });
		NewParticle->SetGlow();
		NewParticle->SetWorldMove();
		NewParticle->SetFadeOut(true);
	}
}