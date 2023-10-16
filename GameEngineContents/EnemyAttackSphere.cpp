#include "PreCompileHeader.h"
#include "EnemyAttackSphere.h"
#include "PhysXSphereComponent.h"

EnemyAttackSphere::EnemyAttackSphere() 
{
}

EnemyAttackSphere::~EnemyAttackSphere() 
{
}


void EnemyAttackSphere::Start()
{
	// Render
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(FIREPLANT_ATT_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXSphereComponent>(FIREPLANT_ATT_PHYSX_SCALE, PhysXFilterGroup::MonsterSkill);
	PhysXComp->SetDynamicPivot(float4::DOWN * 100.0f);
	SetShoot(1000.0f);
}

void EnemyAttackSphere::Update(float _DeltaTime)
{
	AttackBase::Update(_DeltaTime);
}
