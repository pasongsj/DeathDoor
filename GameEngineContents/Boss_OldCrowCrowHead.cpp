#include "PreCompileHeader.h"

#include "Player.h"
#include "PhysXSphereComponent.h"
#include "PhysXControllerComponent.h"

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
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 30.0f, 30.0f });
		m_pSphereComp->TurnOffGravity();
		m_pSphereComp->SetTrigger();
		m_pSphereComp->SetFilterData(PhysXFilterGroup::MonsterSkill);
	}

	GetTransform()->SetLocalScale(float4::ONE * 200.0f);
}

void Boss_OldCrowCrowHead::SetCrowHead(float4 _Pos, float4 _Rot)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);

	CurrentDir = _Rot;
}

void Boss_OldCrowCrowHead::Update(float _DeltaTime)
{
	SetLerpDirection(_DeltaTime);

	m_pSphereComp->SetMoveSpeed(float4::ZERO);
	m_pSphereComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * 100.0f * _DeltaTime);

}

void Boss_OldCrowCrowHead::SetLerpDirection(float _DeltaTime)
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
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