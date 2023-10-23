#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"

void Boss_OldCrow::InitAniamtion()
{
	BossRender = CreateComponent<ContentFBXRenderer>();

	BossRender->SetFBXMesh("OldCrow.FBX", "ContentAniMeshDeffered");
	BossRender->CreateFBXAnimation("Idle", "OldCrow_Idle_Anim.FBX", { 0.033f, true });

	BossRender->CreateFBXAnimation("DashStart", "OldCrow_DashStart_Anim.FBX", { 0.02f, false });
	BossRender->CreateFBXAnimation("Dash", "OldCrow_Dash_Anim.FBX", { 0.033f, true });
	//BossRender->SetAnimationStartFunc("Dash", 1, std::bind(&Boss_OldCrow::, this));
	BossRender->SetAnimationStartFunc("Dash", 3, [this]
		{
			//m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_DASHSPEED);

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED;
		});
	BossRender->SetAnimationStartFunc("Dash", 17, [this]
		{
			//m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_DASHSPEED2 );

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED2;
		});
	BossRender->SetAnimationStartFunc("Dash", 19, [this]
		{
			TurnCheck();
		});

	BossRender->CreateFBXAnimation("TurnLeft", "OldCrow_DashTurnL_Anim.FBX", { 0.033f, false });
	BossRender->SetAnimationStartFunc("TurnLeft", 3, [this]
		{
			IsTurn = true;
		});
	BossRender->SetAnimationStartFunc("TurnLeft", 15, [this]
		{
			IsTurn = false;
		});

	// BossRender->CreateFBXAnimation("TurnRight", "OldCrow_DashTurnR_Anim.FBX", { 0.033f, false });

	BossRender->CreateFBXAnimation("MegaDashPrep", "OldCrow_MegaDashPrep_Anim.FBX", { 0.033f, false });
	BossRender->CreateFBXAnimation("MegaDash", "OldCrow_MegaDash_Anim.FBX", { 0.033f, true });

	BossRender->CreateFBXAnimation("Jump", "OldCrow_Jump_Anim.FBX", { 0.033f, false });
	BossRender->CreateFBXAnimation("Slam", "OldCrow_Slam_Anim.FBX", { 0.033f, false });
	BossRender->CreateFBXAnimation("SlamImpact", "OldCrow_SlamImpact_Anim.FBX", { 0.008f, false });

	BossRender->CreateFBXAnimation("Egg", "OldCrow_Egg_Anim.FBX", { 0.033f, false });

	BossRender->CreateFBXAnimation("Scream", "OldCrow_Scream_Anim.FBX", { 0.033f, false });
	BossRender->CreateFBXAnimation("ScreamMini", "OldCrow_ScreamMini_Anim.FBX", { 0.033f, false });

	BossRender->CreateFBXAnimation("DeathInRunning", "OldCrow_DeathWhileRunning_Anim.FBX", { 0.033f, false });
	BossRender->CreateFBXAnimation("DeathInUpright", "OldCrow_DeathWhileUpright_Anim.FBX", { 0.033f, false });

	GetTransform()->SetLocalScale(float4::ONE * 40.0f);
	BossRender->GetTransform()->SetLocalRotation({ 0, -90, 0 });

	//BossRender->CreateFBXAnimation("", "", { 0.02f, false });
}