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
//void PlayerAttackMagic::Init()
//{
//	MagicRenderer = CreateComponent< ContentFBXRenderer>();
//	MagicRenderer->SetFBXMesh("SphereDefault.fbx","ContentMeshDeffered");
//
//	GetTransform()->SetLocalScale(float4::ONE * 0.2f);
//
//	
//}


void PlayerAttackMagic::Start()
{
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "ContentMeshDeffered");
	AttackRenderer->GetTransform()->SetLocalScale(float4::ONE * 0.2f);
	float4 MagicScale = float4::ONE * 100.0f;
	CreatePhysXAttComp<PhysXSphereComponent>(MagicScale);
}

void PlayerAttackMagic::Update(float _DeltaTime)
{
	PlayerAttackBase::Update(_DeltaTime);
}

//
//void PlayerAttackMagic::SetDir(const float4& _Dir, const float4& _Pos)
//{
//	if (true == _Dir.IsZero())
//	{
//		MsgAssert("Zero dir은 입력할 수 없습니다");
//		return;
//	}
//
//	if (nullptr == PhysXComp)
//	{
//		PhysXComp = CreateComponent< PhysXSphereComponent>();
//		PhysXComp->CreatePhysXActors(float4::ONE * 100.0f, float4::ZERO);
//		PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
//		PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
//		PhysXComp->TurnOffGravity();
//		PhysXComp->SetTrigger();
//	}
//	PhysXComp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, _Pos));
//
//
//	//PhysXComp->SetWorldPosWithParent(_Pos);
//	Dir = _Dir;
//	firetime = GetLiveTime();
//}