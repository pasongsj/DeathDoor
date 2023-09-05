#include "PreCompileHeader.h"
#include "Player.h"



void Player::TestInit()
{


	{
		//Renderer = CreateComponent<GameEngineFBXRenderer>();
		//Renderer->SetFBXMesh("Arrow.FBX", "MeshAniTexture");
		//Renderer->CreateFBXAnimation("Player_Idle", "Arrow.FBX", { 0.01f,true });
		//Renderer->ChangeAnimation("Player_Idle");

		/*Renderer->CreateFBXAnimation("Player_Idle", "Player_Idle.FBX", {0.01f,true});
		AnimationName.push_back("Player_Idle");*/

		//
		//Renderer->CreateFBXAnimation("Player_Walk_S", "Player_Walk_S.FBX", { 0.01f,true }); // 걷기
		//AnimationName.push_back("Player_Walk_S");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Roll", "Player_Roll.FBX", { 0.01f,false });
		//AnimationName.push_back("Player_Roll");
		//
		//
		////////	Renderer->CreateFBXAnimation("Player_Idle2", "Player_Idle.FBX");
		////////AnimationName.push_back("Player_Idle2");
		//
		//Renderer->CreateFBXAnimation("Player_Att_Left", "Player_Att_Left.FBX", { 0.01f,false });
		//AnimationName.push_back("Player_Att_Left");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Att_R", "Player_Att_R.FBX", { 0.01f,false });
		//AnimationName.push_back("Player_Att_R");		

		////
		//////Renderer->CreateFBXAnimation("Player_Charge_Left", "Player_Att_Left.FBX", { 0.01f,false ,0,3});
		//////AnimationName.push_back("Player_Charge_Left");
		//////
		//////
		//////Renderer->CreateFBXAnimation("Player_Charge_R", "Player_Att_R.FBX", { 0.01f,false ,0,3});
		//////AnimationName.push_back("Player_Charge_R");


		////Renderer->CreateFBXAnimation("Player_Att1", "Player_Att1.FBX"); //특수무기??
		////AnimationName.push_back("Player_Att1");
		////
		////
		////Renderer->CreateFBXAnimation("Player_Att2", "Player_Att2.FBX");
		////AnimationName.push_back("Player_Att2");

		//
		//Renderer->CreateFBXAnimation("Player_HitBack", "Player_HitBack.FBX", { 0.01f,false }); // 피격
		//AnimationName.push_back("Player_HitBack");
		//
		//
		//Renderer->CreateFBXAnimation("Player_HitIdle", "Player_HitIdle.FBX", { 0.01f,false });
		//AnimationName.push_back("Player_HitIdle");
		//
		//
		//Renderer->CreateFBXAnimation("Player_SlideAtt", "Player_SlideAtt.FBX", { 0.01f,false }); // 슬라이드 공격
		//AnimationName.push_back("Player_SlideAtt");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Arrow", "Player_Arrow.FBX", { 0.01f,false }); // 스킬 - 화살
		//AnimationName.push_back("Player_Arrow");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Magic", "Player_Magic.FBX"); // 스킬 - 화살
		//AnimationName.push_back("Player_Magic");

		////AnimationName.push_back("Player_Magic");
	}
	//{
	//	float4 scale = Renderer->GetMeshScale();
	//	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
	//	m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
	//
	//
	//	if (GetLevel()->DynamicThis<PhysXTestLevel>() != nullptr)
	//	{
	//		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();
	//
	//
	//		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
	//		m_pCapsuleComp->CreatePhysXActors(pLevel->GetScene(), pLevel->GetPhysics(), vscale);
	//	}
	//}
	{
		GetTransform()->SetLocalScale(float4::ONE * 30.0f/**100.0f*/);
		//GetTransform()->SetLocalRotation({ 90,0,0 });
	}

}

void Player::TestMoveUpdate(float _DeltaTime)
{
	// rot
	if (true == GameEngineInput::IsPress("RotY+"))
	{
		GetTransform()->AddLocalRotation(float4{ 0,1,0 } *m_pSpeed * 0.1f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("RotY-"))
	{
		GetTransform()->AddLocalRotation(float4{ 0,-1,0 } *m_pSpeed * 0.1f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("RotZ+"))
	{
		GetTransform()->AddLocalRotation(float4{ 0,0,1 } *m_pSpeed * 0.1f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("RotZ-"))
	{
		GetTransform()->AddLocalRotation(float4{ 0,0,-1 } *m_pSpeed * 0.1f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("RotX+"))
	{
		GetTransform()->AddLocalRotation(float4{ 1,0,0 } *m_pSpeed * 0.1f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("RotX-"))
	{
		GetTransform()->AddLocalRotation(float4{ -1,0,0 } *m_pSpeed * 0.1f * _DeltaTime);
	}
}



void Player::InitInputKey()
{
	if (false == GameEngineInput::IsKey("PlayerLeft"))
	{
		GameEngineInput::CreateKey("PlayerLeft", 'A');
		GameEngineInput::CreateKey("PlayerRight", 'D');
		GameEngineInput::CreateKey("PlayerUp", 'W');
		GameEngineInput::CreateKey("PlayerDown", 'S');
		GameEngineInput::CreateKey("PlayerRoll", VK_SPACE);
		GameEngineInput::CreateKey("PlayerLBUTTON", VK_LBUTTON);
		GameEngineInput::CreateKey("PlayerRBUTTON", VK_RBUTTON);
		GameEngineInput::CreateKey("PlayerMBUTTON", VK_MBUTTON);
		GameEngineInput::CreateKey("PlayerSkillArrow",	'1');
		GameEngineInput::CreateKey("PlayerSkillMagic",	'2');
		GameEngineInput::CreateKey("PlayerSkillBomb",	'3');
		GameEngineInput::CreateKey("PlayerSkillHook",	'4');
	}
	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}
}




void Player::InitPlayerAnimatioin()
{
	Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("Arrow.FBX", "MeshAniTexture");

	//idle
	Renderer->CreateFBXAnimation("Idle_0", "Idle_0.FBX", { 0.01f,true });
	AnimationName.push_back("Idle_0");

	Renderer->CreateFBXAnimation("Idle_1", "Idle_1.FBX", { 0.01f,true });
	AnimationName.push_back("Idle_1");

	//skill
	Renderer->CreateFBXAnimation("Arrow", "Arrow.FBX", { 0.01f,false });
	AnimationName.push_back("Arrow");

	Renderer->CreateFBXAnimation("Arrow_bomb", "Arrow_bomb.FBX", { 0.01f,false });
	AnimationName.push_back("Arrow_bomb");

	Renderer->CreateFBXAnimation("Arrow_magic", "Arrow_magic.FBX", { 0.01f,false });
	AnimationName.push_back("Arrow_magic");

	Renderer->CreateFBXAnimation("Hookshot", "Hookshot.FBX", { 0.01f,false });
	AnimationName.push_back("Hookshot");

	Renderer->CreateFBXAnimation("Hookshot_fly", "Hookshot_fly.FBX", { 0.01f,true });
	AnimationName.push_back("Hookshot_fly");

	// move
	Renderer->CreateFBXAnimation("Walk", "Walk.FBX", { 0.01f,true });
	AnimationName.push_back("Walk");

	Renderer->CreateFBXAnimation("Run", "Run.FBX", { 0.01f,true });
	AnimationName.push_back("Run");

	//turn
	Renderer->CreateFBXAnimation("Cutscene_turn_half", "Cutscene_turn_half.FBX", { 0.01f,false });
	AnimationName.push_back("Cutscene_turn_half");

	Renderer->CreateFBXAnimation("Cutscene_turn_stopped", "Cutscene_turn_stopped.FBX", { 0.01f,false });
	AnimationName.push_back("Cutscene_turn_stopped");

	Renderer->CreateFBXAnimation("Cutscene_turn_end", "Cutscene_turn_end.FBX", { 0.01f,false });
	AnimationName.push_back("Cutscene_turn_end");

	//roll
	Renderer->CreateFBXAnimation("Roll", "Roll.FBX", { 0.01f,false });
	AnimationName.push_back("Roll");

	Renderer->CreateFBXAnimation("Roll_slash", "Roll_slash.FBX", { 0.01f,false });
	AnimationName.push_back("Roll_slash");

	Renderer->CreateFBXAnimation("Charge_slam_overhead", "Charge_slam_overhead.FBX", { 0.01f,false });// 구르기 마우스 휠
	AnimationName.push_back("Charge_slam_overhead");

	Renderer->CreateFBXAnimation("Roll_slash_end", "Roll_slash_end.FBX", { 0.01f,false });
	AnimationName.push_back("Roll_slash_end");

	//hit 공격당함
	Renderer->CreateFBXAnimation("Hit_back", "Hit_back.FBX", { 0.01f,false });
	AnimationName.push_back("Hit_back");

	Renderer->CreateFBXAnimation("Hit_idle", "Hit_idle.FBX", { 0.01f,true });
	AnimationName.push_back("Hit_idle");

	Renderer->CreateFBXAnimation("Hit_Recover", "Hit_Recover.FBX", { 0.01f,false });
	AnimationName.push_back("Hit_Recover");

	//climb
	Renderer->CreateFBXAnimation("Climbing_ladder", "Climbing_ladder.FBX", { 0.01f,true });
	AnimationName.push_back("Climbing_ladder");

	Renderer->CreateFBXAnimation("Climbing_ladder_down", "Climbing_ladder_down.FBX", { 0.01f,true });
	AnimationName.push_back("Climbing_ladder_down");

	Renderer->CreateFBXAnimation("Climbing_off_ladder_top", "Climbing_off_ladder_top.FBX", { 0.01f,false });
	AnimationName.push_back("Climbing_off_ladder_top");

	//attack
		//left btn
	Renderer->CreateFBXAnimation("Slash_Light_L_new", "Slash_Light_L_new.FBX", { 0.01f,false }); // 일반 좌클릭
	AnimationName.push_back("Slash_Light_L_new");

	Renderer->CreateFBXAnimation("Slash_Light_R_new", "Slash_Light_R_new.FBX", { 0.01f,false }); // 일반 좌클릭
	AnimationName.push_back("Slash_Light_R_new");
	// mid btn
	Renderer->CreateFBXAnimation("Charge_slash_L", "Charge_slash_L.FBX", { 0.01f,false }); 
	AnimationName.push_back("Charge_slash_L");

	Renderer->CreateFBXAnimation("Charge_slash_R", "Charge_slash_R.FBX", { 0.01f,false }); 
	AnimationName.push_back("Charge_slash_R");

	//interaction
	Renderer->CreateFBXAnimation("Push_Lever", "Push_Lever.FBX", { 0.01f,false });
	AnimationName.push_back("Push_Lever");

	Renderer->CreateFBXAnimation("GetItem", "GetItem.FBX", { 0.01f,false }); // 체크필요
	AnimationName.push_back("GetItem");

	// Dead
	Renderer->CreateFBXAnimation("Dead", "Dead.FBX", { 0.01f,true });
	AnimationName.push_back("Dead");

	Renderer->CreateFBXAnimation("Drown", "Drown.FBX", { 0.01f,true }); //물에 빠짐
	AnimationName.push_back("Drown");

	Renderer->CreateFBXAnimation("Falling", "Falling.FBX", { 0.01f,true }); // 바닥에 떨어짐
	AnimationName.push_back("Falling");

	// fly & land
	Renderer->CreateFBXAnimation("Fly", "Fly.FBX", { 0.01f,true }); // 체크필요
	AnimationName.push_back("Fly");

	Renderer->CreateFBXAnimation("Land", "Land.FBX", { 0.01f,false }); // 착지
	AnimationName.push_back("Land");
	//{
	//// 잘 모르겠는 애니메이션

	//	Renderer->CreateFBXAnimation("Injured_fall", "Injured_fall.FBX", { 0.01f,true }); // 돌려야함
	//	AnimationName.push_back("Injured_fall");

	//	Renderer->CreateFBXAnimation("Injured_getup", "Injured_getup.FBX", { 0.01f,true });
	//	AnimationName.push_back("Injured_getup");

	//	Renderer->CreateFBXAnimation("Injured_land", "Injured_land.FBX", { 0.01f,true });
	//	AnimationName.push_back("Injured_land");
	// 
	// 	Renderer->CreateFBXAnimation("Plunge", "Plunge.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge");	
	//
	//	Renderer->CreateFBXAnimation("Plunge_land", "Plunge_land.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge_land");	
	//	
	//	Renderer->CreateFBXAnimation("Plunge_prep", "Plunge_prep.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge_prep");	
	//}

	GetTransform()->SetLocalScale(float4::ONE * 30.0f);
	//GetTransform()->SetLocalRotation({ 90,0,0 });
}
