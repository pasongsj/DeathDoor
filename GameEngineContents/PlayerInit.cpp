#include "PreCompileHeader.h"
#include "Player.h"

#define PlayerScaleRatio 20.0f


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
	Renderer->SetFBXMesh("Player.FBX", "MeshAniTexture");

	//idle
	Renderer->CreateFBXAnimation("Idle_0", "Crow_Player_Idle_0.FBX", { 0.02f,false });
	Renderer->CreateFBXAnimation("Idle_1", "Crow_Player_Idle_1.FBX", { 0.01f,false });

	//skill
	Renderer->CreateFBXAnimation("Arrow", "Crow_Player_Arrow.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Arrow_bomb", "Crow_Player_Arrow_bomb.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Arrow_magic", "Crow_Player_Arrow_magic.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Hookshot", "Crow_Player_Hookshot.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Hookshot_fly", "Crow_Player_Hookshot_fly.FBX", { 0.01f,true });

	// move
	Renderer->CreateFBXAnimation("Walk", "Crow_Player_Walk.FBX", { 0.02f,false ,0,5});
	Renderer->CreateFBXAnimation("Run", "Crow_Player_Run.FBX", { 0.02f,true });

	//roll
	Renderer->CreateFBXAnimation("Roll", "Crow_Player_Roll.FBX", { 0.02f,false });
	Renderer->CreateFBXAnimation("Roll_slash", "Crow_Player_Roll_slash.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Charge_slam_overhead", "Crow_Player_Charge_slam_overhead.FBX", { 0.01f,false });// 구르기 마우스 휠
	Renderer->CreateFBXAnimation("Roll_slash_end", "Crow_Player_Roll_slash_end.FBX", { 0.01f,false });

	//hit 공격당함
	Renderer->CreateFBXAnimation("Hit_back", "Crow_Player_Hit_back.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("Hit_idle", "Crow_Player_Hit_idle.FBX", { 0.01f,true });
	Renderer->CreateFBXAnimation("Hit_Recover", "Crow_Player_Hit_Recover.FBX", { 0.01f,false });

	//climb
	Renderer->CreateFBXAnimation("Climbing_ladder", "Crow_Player_Climbing_ladder.FBX", { 0.02f,true });
	Renderer->CreateFBXAnimation("Climbing_ladder_down", "Crow_Player_Climbing_ladder_down.FBX", { 0.02f,true });
	Renderer->CreateFBXAnimation("Climbing_off_ladder_top", "Crow_Player_Climbing_off_ladder_top.FBX", { 0.02f,false });

	//attack
		//left btn
	Renderer->CreateFBXAnimation("Slash_Light_L_new", "Crow_Player_Slash_Light_R_new.FBX", { 0.01f,false }); // 일반 좌클릭
	Renderer->CreateFBXAnimation("Slash_Light_R_new", "Crow_Player_Slash_Light_L_new.FBX", { 0.01f,false }); // 일반 좌클릭
	// mid btn
	Renderer->CreateFBXAnimation("Charge_slash_L", "Crow_Player_Charge_slash_L.FBX", { 0.01f,false }); 
	Renderer->CreateFBXAnimation("Charge_slash_R", "Crow_Player_Charge_slash_R.FBX", { 0.01f,false }); 

	//interaction
	Renderer->CreateFBXAnimation("Push_Lever", "Crow_Player_Push_Lever.FBX", { 0.01f,false });
	Renderer->CreateFBXAnimation("GetItem", "Crow_Player_GetItem.FBX", { 0.01f,false }); // 체크필요

	// Dead
	Renderer->CreateFBXAnimation("Dead", "Crow_Player_Dead.FBX", { 0.01f,true });
	Renderer->CreateFBXAnimation("Drown", "Crow_Player_Drown.FBX", { 0.01f,true }); //물에 빠짐
	Renderer->CreateFBXAnimation("Falling", "Crow_Player_Falling.FBX", { 0.01f,true }); // 바닥에 떨어짐

	// fly & land
	Renderer->CreateFBXAnimation("Fly", "Crow_Player_Fly.FBX", { 0.01f,true }); // 체크필요
	Renderer->CreateFBXAnimation("Land", "Crow_Player_Land.FBX", { 0.01f,false }); // 착지
	//{
	//// 잘 모르겠는 애니메이션

	//	Renderer->CreateFBXAnimation("Injured_fall", "Crow_Player_Injured_fall.FBX", { 0.01f,true }); // 돌려야함
	//	AnimationName.push_back("Injured_fall");

	//	Renderer->CreateFBXAnimation("Injured_getup", "Crow_Player_Injured_getup.FBX", { 0.01f,true });
	//	AnimationName.push_back("Injured_getup");

	//	Renderer->CreateFBXAnimation("Injured_land", "Crow_Player_Injured_land.FBX", { 0.01f,true });
	//	AnimationName.push_back("Injured_land");
	// 
	// 	Renderer->CreateFBXAnimation("Plunge", "Crow_Player_Plunge.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge");	
	//
	//	Renderer->CreateFBXAnimation("Plunge_land", "Crow_Player_Plunge_land.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge_land");	
	//	
	//	Renderer->CreateFBXAnimation("Plunge_prep", "Crow_Player_Plunge_prep.FBX", { 0.01f,true });
	//	AnimationName.push_back("Plunge_prep");	
	//}

	GetTransform()->SetLocalScale(float4::ONE * PlayerScaleRatio);
}


