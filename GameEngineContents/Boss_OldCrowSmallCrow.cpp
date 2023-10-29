#include "PreCompileHeader.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "Player.h"
#include "PhysXSphereComponent.h"

#include "Boss_OldCrowSmallCrow.h"

Boss_OldCrowSmallCrow::Boss_OldCrowSmallCrow() 
{
}

Boss_OldCrowSmallCrow::~Boss_OldCrowSmallCrow() 
{
}

void Boss_OldCrowSmallCrow::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_CrowMini.FBX", "ContentAniMeshDeffered");
	Renderer->CreateFBXAnimation("Fly", "Boss_OldCrow_CrowMiniFly.FBX", { 0.033f, true });

	Renderer->ChangeAnimation("Fly");

	if (m_pSphereComp == nullptr)
	{
		m_pSphereComp = CreateComponent<PhysXSphereComponent>();

		m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 50.0f, 50.0f });
		m_pSphereComp->TurnOffGravity();
		m_pSphereComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);

		m_pSphereComp->CreateSubShape(SubShapeType::SPHERE, float4{ 50, 50, 50 });
		m_pSphereComp->SetSubShapeFilter(PhysXFilterGroup::MonsterSkill);
	}

	Angle = GameEngineRandom::MainRandom.RandomFloat(0, 35);
	Angle *= 10.0f;

	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
}

void Boss_OldCrowSmallCrow::SetLerpDirection(float _DeltaTime)
{
	if (GetLiveTime() > 1.5f)
	{
		m_pSphereComp->TurnOnGravity();

		float4 PlayerPos = TargetPosition;
		PlayerPos.y = 0.0f;
		float4 EnemyPos = GetTransform()->GetWorldPosition();
		EnemyPos.y = 0.0f;
		Dir = (PlayerPos - EnemyPos).NormalizeReturn();

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
}

void Boss_OldCrowSmallCrow::SetDirection()
{
	if (GetLiveTime() > 1.0f)
	{
		float4 TargetPos = TargetPosition;
		float4 EnemyPos = GetTransform()->GetWorldPosition();
		
		Dir = (TargetPos - EnemyPos).NormalizeReturn();

		m_pSphereComp->SetWorldPosWithParent(EnemyPos, Dir);
	}
}


void Boss_OldCrowSmallCrow::Update(float _DeltaTime)
{
	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))
	{
		Death();
		return;
	}

	SetTargetTransform(_DeltaTime);
	SetLerpDirection(_DeltaTime);
	//SetDirection();

	if (GetTransform()->GetWorldPosition().y <= 30.0f)
	{
		m_pSphereComp->TurnOffGravity();
	}

	m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_SMALLCROWSPEED);


}

void Boss_OldCrowSmallCrow::SetSmallCrow(float4 _Pos, float4 _Rot)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);
}

void Boss_OldCrowSmallCrow::SetTargetTransform(float _DeltaTime)
{
	Angle += BOSS_OLDCROW_OrbitSpeed * _DeltaTime;

	float4 TargetPos = Player::MainPlayer->GetTransform()->GetWorldPosition() + float4{ 0, 0, BOSS_OLDCROW_OrbitDistance };
	float4 Dir = TargetPos - Player::MainPlayer->GetTransform()->GetWorldPosition();

	float4 Rot = float4::ZERO;
	Rot.y = Angle;

	Dir.RotaitonYDeg(Angle);

	TargetPosition = Player::MainPlayer->GetTransform()->GetWorldPosition() + Dir;

	int a = 0;
}