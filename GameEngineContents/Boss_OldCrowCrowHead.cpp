#include "PreCompileHeader.h"

#include "Player.h"
#include "PhysXSphereComponent.h"
#include "PhysXControllerComponent.h"

#include "Boss_OldCrowCrowHead.h"

#include "DustParticle.h"
#include "ContentLevel.h"


Boss_OldCrowCrowHead::Boss_OldCrowCrowHead() 
{
}

Boss_OldCrowCrowHead::~Boss_OldCrowCrowHead() 
{
}

void Boss_OldCrowCrowHead::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_CrowHead.FBX", "NoLight");
	Renderer->CreateFBXAnimation("Fly", "Boss_OldCrow_CrowHeadFly.FBX", { 0.033f, true });
	Renderer->GetTransform()->AddLocalPosition(float4{ 0.0f, 0.2f, 0.0f });
	Renderer->SetColor(float4::BLACK, 0.9f);

	Renderer->ChangeAnimation("Fly");

	GetTransform()->SetLocalScale(float4::ONE * 200.0f);

	IsAttacked = false;
	IsCreated = false;
}

void Boss_OldCrowCrowHead::SetCrowHead(float4 _Pos, float4 _Rot, std::shared_ptr<PhysXControllerComponent> _BossPhysXComponent)
{
	_Pos.y += 50.0f;

	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldRotation(_Rot);

	BossPhysXComponent = _BossPhysXComponent;
}

void Boss_OldCrowCrowHead::Update(float _DeltaTime)
{
	//생성되기 전 연출을 위한 (바닥에 닿으면 Create = true)
	

	if (false == IsCreated)
	{
		CreateDustParticle(_DeltaTime);

		if (GetTransform()->GetWorldPosition().y <= 5.0f)
		{
			if (m_pSphereComp == nullptr)
			{
				m_pSphereComp = CreateComponent<PhysXControllerComponent>();

				m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
				m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 101.0f, 100.0f });
				m_pSphereComp->TurnOffGravity();
				m_pSphereComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);

				m_pSphereComp->CreateSubShape(SubShapeType::BOX, float4{ 100, 50, 100 }, float4 {0, 0, 40});
				m_pSphereComp->SetSubShapeFilter(PhysXFilterGroup::MonsterSkill);
				m_pSphereComp->AttachShape();

			}

			if (nullptr != Player::MainPlayer)
			{
				m_pSphereComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
			}

			if (nullptr != BossPhysXComponent)
			{
				m_pSphereComp->SetFilter(*BossPhysXComponent->GetController());
			}

			m_pSphereComp->RigidSwitch(false);



			IsCreated = true;
		}
		else
		{
			GetTransform()->AddWorldPosition(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_CROWHEADSPEED * _DeltaTime);
			
			float RotSpeed = 30.0f;

			GetTransform()->AddWorldRotation(float4{ _DeltaTime * 90.0f, 0, 0 });

		}

		return;
	}

	//플레이어 공격 받기 전 업데이트
	if (false == IsAttacked)
	{
		SetLerpDirection(_DeltaTime);
		m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_CROWHEADSPEED);
		CreateDustParticle(_DeltaTime);
		ParryingCheck();

		if (true == CheckCollision(PhysXFilterGroup::PlayerDynamic))
		{
			Death();
			return;
		}
	}
	//플레이어 공격 받은 후 업데이트 (패링 이후)
	else
	{
		CreateDustParticle(_DeltaTime, { 0.99f, 0.2f, 0.4f, 1.0f}, true);

		m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_CROWHEADPARRYINGSPEED);


		ParryingTime += _DeltaTime;	
	}


	if (ParryingTime > 5.0f)
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

	float4 LerpDir = float4::LerpClamp(CurrentDir, Dir, _DeltaTime / 10.0f);
	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, LerpDir);

	CurrentDir = LerpDir;

	m_pSphereComp->SetRotation(-CalRot);
}

void Boss_OldCrowCrowHead::ParryingCheck() //패링 여부
{
	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))
	{
		IsAttacked = true;

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		PlayerPos.y = 0.0f;
		float4 EnemyPos = GetTransform()->GetWorldPosition();
		EnemyPos.y = 0.0f;

		Dir = EnemyPos - PlayerPos;

		float4 CalRot = float4::ZERO;
		CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, Dir);

		m_pSphereComp->SetRotation(-CalRot);

		m_pSphereComp->DetachShape();
		m_pSphereComp->SetSubShapeFilter(PhysXFilterGroup::PlayerSkill);
		m_pSphereComp->AttachShape();

		Renderer->SetColor({ 0.99f, 0.1f, 0.2f, 1.0f }, 5.0f);
		//m_pSphereComp->SetTrigger();

		GameEngineSound::Play("OldCrow_CrowHeadParrying.mp3");

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

void Boss_OldCrowCrowHead::CreateDustParticle(float _Delta, float4 _RGB, bool _isGlow)
{
	ParticleCount += _Delta;

	if (ParticleCount >= 0.05f)
	{
		ParticleCount = 0.0f;

		std::shared_ptr<DustParticle> Particle = CreateComponent<DustParticle>();

		Particle->GetTransform()->SetParent(GetLevel()->DynamicThis<ContentLevel>()->GetPivotActor()->GetTransform());
		Particle->GetTransform()->SetWorldPosition(Renderer->GetTransform()->GetWorldPosition() + float4{ 0.0f, 0.0f, 0.0f });
		Particle->GetTransform()->SetWorldScale({ 100.0f, 100.0f });
		Particle->BillboardingOff();
		Particle->SetColor(_RGB);
		Particle->SetFadeOut(true);
		Particle->GetTransform()->SetWorldRotation(float4{90.0f, 0.0f, 0.0f});

		if (_isGlow == true)
		{
			Particle->SetColor(_RGB * 5.0f);
		}
	}
}