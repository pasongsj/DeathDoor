#include "PreCompileHeader.h"
#include "EnemyAttackSphere.h"
#include "PhysXSphereComponent.h"

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
}





void EnemyAttackSphere::Update(float _DeltaTime)
{
	AttackBase::Update(_DeltaTime);
}
