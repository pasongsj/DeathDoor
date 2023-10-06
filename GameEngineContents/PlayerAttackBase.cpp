#include "PreCompileHeader.h"
#include "PlayerAttackBase.h"

#include "ContentFBXRenderer.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXSphereComponent.h"

PlayerAttackBase::PlayerAttackBase()
{
}

PlayerAttackBase::~PlayerAttackBase()
{
}


void PlayerAttackBase::Start()
{

}

void PlayerAttackBase::Update(float _DeltaTime)
{
	if (false == isShoot)
	{
		return;
	}
	if (true == CheckCollision(PhysXFilterGroup::MonsterDynamic) || GetLiveTime() > FireTime + 10.0f)
	{
		Death();
		return;
	}
	PhysXComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	PhysXComp->SetMoveSpeed(Dir * 1000.0f);
	isPhysXCollision = 0;

}


void PlayerAttackBase::SetTrans(const float4& _Dir, const float4& _Pos)
{
	if (true == _Dir.IsZero())
	{
		MsgAssert("Zero dir은 입력할 수 없습니다");
		return;
	}

	if (nullptr == PhysXComp)
	{
		MsgAssert("PhysX Component가 생성되지 않았습니다.");
		return;
	}
	PhysXComp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, _Pos));
	Dir = _Dir;
	FireTime = GetLiveTime();
}

//
//void PlayerAttackBase::SetAttackType(AttackType _Type)
//{
//	CurType = _Type;
//	switch (CurType)
//	{
//	case AttackType::BASE_ATT:
//	{
//		PhysXComp = CreateComponent< PhysXBoxComponent>();
//
//		break;
//	}
//	case AttackType::ARROW:
//	{
//		PhysXComp = CreateComponent< PhysXCapsuleComponent>();
//		break;
//	}
//	case AttackType::MAGIC:
//	{
//		PhysXComp = CreateComponent< PhysXSphereComponent>();
//		break;
//	}
//	case AttackType::BOMB:
//	{
//		PhysXComp = CreateComponent< PhysXSphereComponent>();
//		break;
//	}
//	default:
//	{
//		break;
//	}
//	}
//	PhysXComp->CreatePhysXActors(float4::ONE * 100.0f, float4::ZERO);
//	PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
//	PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
//	PhysXComp->TurnOffGravity();
//	PhysXComp->SetTrigger();
//}
