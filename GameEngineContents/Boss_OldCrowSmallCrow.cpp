#include "PreCompileHeader.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "Player.h"
#include "PhysXSphereComponent.h"
#include "PhysXControllerComponent.h"
#include "PhysXCapsuleComponent.h"

#include "Boss_OldCrowSmallCrow.h"

Boss_OldCrowSmallCrow::Boss_OldCrowSmallCrow() 
{
}

Boss_OldCrowSmallCrow::~Boss_OldCrowSmallCrow() 
{
	Idle.Stop();
}

void Boss_OldCrowSmallCrow::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_CrowMini.FBX", "ContentAniMeshDeffered");
	Renderer->CreateFBXAnimation("Fly", "Boss_OldCrow_CrowMiniFly.FBX", { 0.033f, true });

	Renderer->ChangeAnimation("Fly");
	Renderer->SetColor(float4::BLACK, 0.9f);

	if (m_pSphereComp == nullptr)
	{
		m_pSphereComp = CreateComponent<PhysXControllerComponent>();

		m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 51.0f, 50.0f });
		m_pSphereComp->TurnOffGravity();
		m_pSphereComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		//m_pSphereComp->SetTrigger();

		m_pSphereComp->CreateSubShape(SubShapeType::BOX, float4{ 100, 100, 100 }, float4 {0, 0, 0});
		m_pSphereComp->SetSubShapeFilter(PhysXFilterGroup::MonsterSkill);
		m_pSphereComp->AttachShape();
	}

	Idle = GameEngineSound::Play("OldCrow_SmallCrowIdle.mp3");
	Idle.SetLoop();

	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
}

void Boss_OldCrowSmallCrow::SetLerpDirection(float _DeltaTime)
{
	if (GetLiveTime() > 1.5f)
	{
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

		m_pSphereComp->SetRotation(-CalRot);
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
		GameEngineSoundPlayer DeathSound = GameEngineSound::Play("OldCrow_SmallCrowDeath.mp3");
		DeathSound.SetVolume(0.5f);

		Death();
		return;
	}

	if (true == CheckCollision(PhysXFilterGroup::PlayerDynamic) && false == IsStickPlayer)
	{
		//슬로우 걸어주고
		IsStickPlayer = true;
		StickPos = GetTransform()->GetWorldPosition() - Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
		StickPos.y = 30.0f;
	}

	if (false == IsStickPlayer)
	{
		SetTargetTransform(_DeltaTime);
		SetLerpDirection(_DeltaTime);

		if (GetLiveTime() > 1.5f && false == CreatedGravity)
		{
			CreatedGravity = true;
			m_pSphereComp->TurnOnGravity();
		}

		if (GetTransform()->GetWorldPosition().y <= 30.0f)
		{
			m_pSphereComp->TurnOffGravity();
		}

		// 10초 이후 점점 공전 거리가 짧아짐
		if (GetLiveTime() > 10.0f)
		{
			CurrentDistance -= 100 * _DeltaTime;

			if (CurrentDistance < 0.0f)
			{
				CurrentDistance = 0.0f;
			}
		}
		m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_SMALLCROWSPEED);
	}
	else
	{
		m_pSphereComp->SetWorldPosWithParent(Player::MainPlayer->GetPhysXComponent()->GetWorldPosition() + StickPos);
	}


}

void Boss_OldCrowSmallCrow::SetSmallCrow(float4 _Pos, float4 _Rot, float _TargetAngle, std::shared_ptr<PhysXControllerComponent> _BossPhysXComponent)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);

	Angle = _TargetAngle;
	
	if (nullptr != Player::MainPlayer)
	{
		m_pSphereComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
	}

	if (nullptr != _BossPhysXComponent)
	{
		m_pSphereComp->SetFilter(*_BossPhysXComponent->GetController());
	}

	m_pSphereComp->RigidSwitch(false);
}

void Boss_OldCrowSmallCrow::SetTargetTransform(float _DeltaTime)
{
	Angle += BOSS_OLDCROW_OrbitSpeed * _DeltaTime;

	float4 TargetPos = Player::MainPlayer->GetTransform()->GetWorldPosition() + float4{ 0, 0, CurrentDistance };
	float4 Dir = TargetPos - Player::MainPlayer->GetTransform()->GetWorldPosition();

	float4 Rot = float4::ZERO;
	Rot.y = Angle;

	Dir.RotaitonYDeg(Angle);

	TargetPosition = Player::MainPlayer->GetTransform()->GetWorldPosition() + Dir;

	int a = 0;
}