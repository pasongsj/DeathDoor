#include "PreCompileHeader.h"

#include "Boss_OldCrowEgg.h"

#include "Boss_OldCrow.h"

void Boss_OldCrow::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();

	EnemyRenderer->SetFBXMesh("OldCrow.FBX", "ContentAniMeshDeffered");
	EnemyRenderer->CreateFBXAnimation("Idle", "OldCrow_Idle_Anim.FBX", { 0.033f, true });

	EnemyRenderer->CreateFBXAnimation("DashStart", "OldCrow_DashStart_Anim.FBX", { 0.02f, false });
	EnemyRenderer->CreateFBXAnimation("Dash", "OldCrow_Dash_Anim.FBX", { 0.033f, true });
	//BossRender->SetAnimationStartFunc("Dash", 1, std::bind(&Boss_OldCrow::, this));
	EnemyRenderer->SetAnimationStartFunc("Dash", 3, [this]
		{
			//m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_DASHSPEED);

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED;
		});
	EnemyRenderer->SetAnimationStartFunc("Dash", 17, [this]
		{
			//m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_DASHSPEED2 );

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED2;
		});
	EnemyRenderer->SetAnimationStartFunc("Dash", 19, [this]
		{
			TurnCheck();
		});

	EnemyRenderer->CreateFBXAnimation("TurnLeft", "OldCrow_DashTurnL_Anim.FBX", { 0.033f, false });
	EnemyRenderer->SetAnimationStartFunc("TurnLeft", 3, [this]
		{
			IsTurn = true;
		});
	EnemyRenderer->SetAnimationStartFunc("TurnLeft", 15, [this]
		{
			IsTurn = false;
		});

	// BossRender->CreateFBXAnimation("TurnRight", "OldCrow_DashTurnR_Anim.FBX", { 0.033f, false });

	EnemyRenderer->CreateFBXAnimation("MegaDashPrep", "OldCrow_MegaDashPrep_Anim.FBX", { 0.033f, false });
	EnemyRenderer->CreateFBXAnimation("MegaDash", "OldCrow_MegaDash_Anim.FBX", { 0.033f, true });

	EnemyRenderer->CreateFBXAnimation("Jump", "OldCrow_Jump_Anim.FBX", { 0.033f, false });
	EnemyRenderer->CreateFBXAnimation("Slam", "OldCrow_Slam_Anim.FBX", { 0.033f, false });
	EnemyRenderer->CreateFBXAnimation("SlamImpact", "OldCrow_SlamImpact_Anim.FBX", { 0.008f, false });

	EnemyRenderer->CreateFBXAnimation("Egg", "OldCrow_Egg_Anim.FBX", { 0.033f, false });
	EnemyRenderer->SetAnimationStartFunc("Egg", 80, [this]
		{
			std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent<GameEngineComponent>();
			BonePivot->GetTransform()->SetParent(GetTransform());
			BonePivot->GetTransform()->SetLocalPosition(float4{ 0, 14, 2 });

			float Value = 5.0f;

			BonePivot->GetTransform()->AddLocalRotation({ -70.0f, 0.0f, 0.0f });

			float4 EggDir = float4::ZERO;
			
			std::shared_ptr<Boss_OldCrowEgg> CrowEgg = GetLevel()->CreateActor<Boss_OldCrowEgg>();
			CrowEgg->SetCrowEgg(BonePivot->GetTransform()->GetWorldPosition(), BonePivot->GetTransform()->GetWorldRotation(), BonePivot->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition());

		});

	EnemyRenderer->CreateFBXAnimation("Scream", "OldCrow_Scream_Anim.FBX", { 0.033f, false });
	EnemyRenderer->CreateFBXAnimation("ScreamMini", "OldCrow_ScreamMini_Anim.FBX", { 0.033f, false });
	EnemyRenderer->SetAnimationStartFunc("ScreamMini", 18, [this]
		{
			StateCalBool = true;
		});

	EnemyRenderer->CreateFBXAnimation("DeathInRunning", "OldCrow_DeathWhileRunning_Anim.FBX", { 0.033f, false });
	EnemyRenderer->CreateFBXAnimation("DeathInUpright", "OldCrow_DeathWhileUpright_Anim.FBX", { 0.033f, false });

	GetTransform()->SetLocalScale(float4::ONE * 40.0f);
	EnemyRenderer->GetTransform()->SetLocalRotation({ 0, -90, 0 });

	EnemyRenderer->ChangeAnimation("Idle");

	//BossRender->CreateFBXAnimation("", "", { 0.02f, false });
}