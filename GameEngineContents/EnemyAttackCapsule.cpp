#include "PreCompileHeader.h"
#include "EnemyAttackCapsule.h"
#include "PhysXCapsuleComponent.h"

EnemyAttackCapsule::EnemyAttackCapsule() 
{

}

EnemyAttackCapsule::~EnemyAttackCapsule()
{
}
void EnemyAttackCapsule::SetRender(const float4& _RenderScale, const float4& _RenderRotate, const std::string_view& _Mesh)
{
	if (nullptr == AttackRenderer)
	{
		AttackRenderer = CreateComponent< ContentFBXRenderer>();
	}
	if ("" == _Mesh)
	{
		AttackRenderer->SetFBXMesh("ARROW_MESH.fbx", "ContentMeshDeffered");
	}
	else
	{
		AttackRenderer->SetFBXMesh(_Mesh.data(), "ContentMeshDeffered");
	}
	AttackRenderer->GetTransform()->SetLocalScale(_RenderScale);
	AttackRenderer->GetTransform()->SetLocalRotation(_RenderRotate);
	AttackRenderer->SetGlowToUnit(0, 0);
}

void EnemyAttackCapsule::SetPhysXComp(const float4& _PhysXScale, const float4& _Pivot, const float4& _Axis)
{
	// PhysX
	CreatePhysXAttComp<PhysXCapsuleComponent>(_PhysXScale, PhysXFilterGroup::MonsterSkill);
	PhysXComp->SetDynamicPivot(_Pivot);
	PhysXComp->SetShapeAxis(0.0f, _Axis);
	SetDestTarget(PhysXFilterGroup::PlayerDynamic);

}


void EnemyAttackCapsule::Update(float _DeltaTime)
{
	AttackBase::Update(_DeltaTime);
}
