#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"

void Boss_OldCrow::InitAniamtion()
{
	BossRender = CreateComponent<GameEngineFBXRenderer>();

	BossRender->SetFBXMesh("OldCrow.FBX", "MeshAniTexture");
	BossRender->CreateFBXAnimation("Idle", "OldCrow_Idle.fbx", { 0.02f, true });

	BossRender->CreateFBXAnimation("DashStart", "OldCrow_DashStart.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("Dash", "OldCrow_Dash.fbx", { 0.033f, true });
	BossRender->CreateFBXAnimation("TurnLeft", "OldCrow_DashTurnL.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("TurnRight", "OldCrow_DashTurnR.fbx", { 0.02f, false });

	BossRender->CreateFBXAnimation("MegaDashPrep", "OldCrow_MegaDashPrep.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("MegaDash", "OldCrow_MegaDash.fbx", { 0.02f, true });

	BossRender->CreateFBXAnimation("Jump", "OldCrow_Jump.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("Slam", "OldCrow_Slam.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("SlamImpact", "OldCrow_SlamImpact.fbx", { 0.02f, false });

	BossRender->CreateFBXAnimation("Egg", "OldCrow_Egg.fbx", { 0.02f, false });

	BossRender->CreateFBXAnimation("Scream", "OldCrow_Scream.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("ScreamMini", "OldCrow_ScreamMini.fbx", { 0.02f, false });

	BossRender->CreateFBXAnimation("DeathInRunning", "OldCrow_DeathInRunning.fbx", { 0.02f, false });
	BossRender->CreateFBXAnimation("DeathInUpright", "OldCrow_DeathInUpright.fbx", { 0.02f, false });


	BossRender->ChangeAnimation("Idle");


	//BossRender->CreateFBXAnimation("", "", { 0.02f, false });
}