#include "PreCompileHeader.h"

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
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 30.0f, 30.0f });
		m_pSphereComp->TurnOffGravity();
		//m_pSphereComp->SetTrigger();
		m_pSphereComp->SetFilterData(PhysXFilterGroup::CrowDebuff);
	}

	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
}

void Boss_OldCrowSmallCrow::SetLerpDirection(float _DeltaTime)
{
	if (GetLiveTime() > 1.5f)
	{
		m_pSphereComp->TurnOnGravity();

		float4 PlayerPos = TargetTransform->GetTransform()->GetWorldPosition();
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
		float4 TargetPos = TargetTransform->GetTransform()->GetWorldPosition();
		float4 EnemyPos = GetTransform()->GetWorldPosition();
		
		Dir = (TargetPos - EnemyPos).NormalizeReturn();

		m_pSphereComp->SetWorldPosWithParent(EnemyPos, Dir);
	}
}


void Boss_OldCrowSmallCrow::Update(float _DeltaTime)
{
	SetLerpDirection(_DeltaTime);
	//SetDirection();

	m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * 800.0f);

	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))
	{
		Death();
		return;
	}
}

void Boss_OldCrowSmallCrow::SetSmallCrow(float4 _Pos, float4 _Rot, std::shared_ptr<GameEngineActor> _TargetTransform)
{
	TargetTransform = _TargetTransform;

	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);
}
