#include "PreCompileHeader.h"

#include "Player.h"
#include "PhysXSphereComponent.h"

#include "Boss_OldCrowCrowHead.h"

Boss_OldCrowCrowHead::Boss_OldCrowCrowHead() 
{
}

Boss_OldCrowCrowHead::~Boss_OldCrowCrowHead() 
{
}

void Boss_OldCrowCrowHead::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_CrowHead.FBX", "ContentAniMeshDeffered");
	Renderer->CreateFBXAnimation("Fly", "Boss_OldCrow_CrowHeadFly.FBX", { 0.033f, true });

	Renderer->ChangeAnimation("Fly");

	if (m_pSphereComp == nullptr)
	{
		m_pSphereComp = CreateComponent<PhysXSphereComponent>();

		m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 100.0f, 100.0f });
		m_pSphereComp->TurnOffGravity();
		//m_pSphereComp->SetTrigger();
		m_pSphereComp->SetFilterData(PhysXFilterGroup::MonsterSkill);
	}

	GetTransform()->SetLocalScale(float4::ONE * 200.0f);

	IsAttacked = false;
}

void Boss_OldCrowCrowHead::SetCrowHead(float4 _Pos, float4 _Rot)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);

	CurrentDir = _Rot;
}

void Boss_OldCrowCrowHead::Update(float _DeltaTime)
{
	if (false == IsAttacked)
	{
		SetLerpDirection(_DeltaTime);
		m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * 200.0f);
		AttackCheck();
	}
	else
	{
		m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * 500.0f);
	}

	if (true == CheckCollision(PhysXFilterGroup::Obstacle))
	{
		Death();
		return;
	}

	//데미지 주고
	if (true == CheckCollision(PhysXFilterGroup::PlayerDynamic))
	{
		Death();
		return;
	}
}

void Boss_OldCrowCrowHead::SetLerpDirection(float _DeltaTime)
{
	Dir = GetPlayerDir();

	if (Dir == CurrentDir)
	{
		return;
	}

	float4 LerpDir = float4::LerpClamp(CurrentDir, Dir, _DeltaTime);
	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, LerpDir);

	CurrentDir = LerpDir;

	m_pSphereComp->SetChangedRot(-CalRot);
}

void Boss_OldCrowCrowHead::AttackCheck()
{
	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))
	{
		IsAttacked = true;

		Dir = GetPlayerDir();

		float4 CalRot = float4::ZERO;
		CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, Dir);

		m_pSphereComp->SetChangedRot(-CalRot);
	}
}

float4 Boss_OldCrowCrowHead::GetPlayerDir()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	PlayerPos.y = 0.0f;
	float4 EnemyPos = GetTransform()->GetWorldPosition();
	EnemyPos.y = 0.0f;

	return (PlayerPos - EnemyPos).NormalizeReturn();
}