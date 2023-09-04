#include "PrecompileHeader.h"
#include "Player.h"
#include "ContentFBXRenderer.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXTestLevel.h"
#include "PhysXCapsuleComponent.h"

Player* Player::MainPlayer = nullptr;


Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}


void Player::InitPlayer()
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
	}
}

void Player::CheckAllAnimation()
{


	////Renderer->CreateFBXAnimation("Arrow", "Arrow.FBX", { 0.01f,true });
	////AnimationName.push_back("Arrow");	
	////
	////Renderer->CreateFBXAnimation("Arrow_bomb", "Arrow_bomb.FBX", { 0.01f,true });
	////AnimationName.push_back("Arrow_bomb");
	////
	////Renderer->CreateFBXAnimation("Arrow_magic", "Arrow_magic.FBX", { 0.01f,true });
	////AnimationName.push_back("Arrow_magic");	
		
	////Renderer->CreateFBXAnimation("Brace", "Brace.FBX", { 0.01f,true });
	////AnimationName.push_back("Brace");	
	////	
	////Renderer->CreateFBXAnimation("Charge_Heavy_L", "Charge_Heavy_L.FBX", { 0.01f,true });//마우스 휠 차지
	////AnimationName.push_back("Charge_Heavy_L");
	////Renderer->CreateFBXAnimation("Charge_Heavy_R", "Charge_Heavy_R.FBX", { 0.01f,true });//마우스 휠 차지
	////AnimationName.push_back("Charge_Heavy_R");
	
	
	////Renderer->CreateFBXAnimation("Charge_slash_L", "Charge_slash_L.FBX", { 0.01f,true }); // 일반 좌클릭
	////AnimationName.push_back("Charge_slash_L");
	////
	Renderer->CreateFBXAnimation("Charge_slam_overhead", "Charge_slam_overhead.FBX", { 0.01f,true });// 구르기 마우스 휠
	AnimationName.push_back("Charge_slam_overhead");

	////Renderer->CreateFBXAnimation("Charge_slash_R", "Charge_slash_R.FBX", { 0.01f,true }); // 일반 좌클릭
	////AnimationName.push_back("Charge_slash_R");	
	////
	////Renderer->CreateFBXAnimation("Climbing_ladder", "Climbing_ladder.FBX", { 0.01f,true });
	////AnimationName.push_back("Climbing_ladder");
	////	
	////Renderer->CreateFBXAnimation("Climbing_ladder_down", "Climbing_ladder_down.FBX", { 0.01f,true });
	////AnimationName.push_back("Climbing_ladder_down");	
	////
	////Renderer->CreateFBXAnimation("Climbing_off_ladder_top", "Climbing_off_ladder_top.FBX", { 0.01f,true });
	////AnimationName.push_back("Climbing_off_ladder_top");

	////Renderer->CreateFBXAnimation("Cutscene_turn_end", "Cutscene_turn_end.FBX", { 0.01f,true });
	////AnimationName.push_back("Cutscene_turn_end");	
	////
	////Renderer->CreateFBXAnimation("Cutscene_turn_half", "Cutscene_turn_half.FBX", { 0.01f,true });
	////AnimationName.push_back("Cutscene_turn_half");
	////	
	////Renderer->CreateFBXAnimation("Cutscene_turn_stopped", "Cutscene_turn_stopped.FBX", { 0.01f,true });
	////AnimationName.push_back("Cutscene_turn_stopped");	

	////Renderer->CreateFBXAnimation("Dead", "Dead.FBX", { 0.01f,true });
	////AnimationName.push_back("Dead");	
	////
	////Renderer->CreateFBXAnimation("Drown", "Drown.FBX", { 0.01f,true });
	////AnimationName.push_back("Drown");
	////	
	////Renderer->CreateFBXAnimation("Falling", "Falling.FBX", { 0.01f,true });
	////AnimationName.push_back("Falling");	
	
	//Renderer->CreateFBXAnimation("Fly", "Fly.FBX", { 0.01f,true }); // 체크필요
	//AnimationName.push_back("Fly");

	//
	//Renderer->CreateFBXAnimation("GetItem", "GetItem.FBX", { 0.01f,true }); // 체크필요
	//AnimationName.push_back("GetItem");
	//	
	//Renderer->CreateFBXAnimation("Hit_back", "Hit_back.FBX", { 0.01f,true });
	//AnimationName.push_back("Hit_back");	
	//
	//Renderer->CreateFBXAnimation("Hit_idle", "Hit_idle.FBX", { 0.01f,true });
	//AnimationName.push_back("Hit_idle");
	//
	//Renderer->CreateFBXAnimation("Hit_Recover", "Hit_Recover.FBX", { 0.01f,true });
	//AnimationName.push_back("Hit_Recover");	
	
	////Renderer->CreateFBXAnimation("Hookshot", "Hookshot.FBX", { 0.01f,true });
	////AnimationName.push_back("Hookshot");
	////	
	////Renderer->CreateFBXAnimation("Hookshot_fly", "Hookshot_fly.FBX", { 0.01f,true });
	////AnimationName.push_back("Hookshot_fly");	
	////
	////Renderer->CreateFBXAnimation("Idle_0", "Idle_0.FBX", { 0.01f,true });
	////AnimationName.push_back("Idle_0");
	////
	////Renderer->CreateFBXAnimation("Idle_1", "Idle_1.FBX", { 0.01f,true });
	////AnimationName.push_back("Idle_1");
	//	
	////Renderer->CreateFBXAnimation("Injured_fall", "Injured_fall.FBX", { 0.01f,true }); // 돌려야함
	////AnimationName.push_back("Injured_fall");	
	////
	////Renderer->CreateFBXAnimation("Injured_getup", "Injured_getup.FBX", { 0.01f,true });
	////AnimationName.push_back("Injured_getup");
	////
	////Renderer->CreateFBXAnimation("Injured_land", "Injured_land.FBX", { 0.01f,true });
	////AnimationName.push_back("Injured_land");	
	////
	////Renderer->CreateFBXAnimation("Land", "Land.FBX", { 0.01f,true }); // 착지
	////AnimationName.push_back("Land");
	//	
	//뭔지 모르겠음//Renderer->CreateFBXAnimation("Plunge", "Plunge.FBX", { 0.01f,true });
	//뭔지 모르겠음//AnimationName.push_back("Plunge");	
	//뭔지 모르겠음//////
	//뭔지 모르겠음////Renderer->CreateFBXAnimation("Plunge_land", "Plunge_land.FBX", { 0.01f,true });
	//뭔지 모르겠음////AnimationName.push_back("Plunge_land");	
	//뭔지 모르겠음////	
	//뭔지 모르겠음//Renderer->CreateFBXAnimation("Plunge_prep", "Plunge_prep.FBX", { 0.01f,true });
	//뭔지 모르겠음//AnimationName.push_back("Plunge_prep");	


	////Renderer->CreateFBXAnimation("Push_Lever", "Push_Lever.FBX", { 0.01f,true });
	////AnimationName.push_back("Push_Lever");	
	////
	////Renderer->CreateFBXAnimation("Roll", "Roll.FBX", { 0.01f,true });
	////AnimationName.push_back("Roll");


	//Renderer->CreateFBXAnimation("Roll_slash", "Roll_slash.FBX", { 0.01f,true }); 
	//AnimationName.push_back("Roll_slash");
	//	
	//Renderer->CreateFBXAnimation("Roll_slash_end", "Roll_slash_end.FBX", { 0.01f,true });
	//AnimationName.push_back("Roll_slash_end");	
	//
	//Renderer->CreateFBXAnimation("Run", "Run.FBX", { 0.01f,true });
	//AnimationName.push_back("Run");
	//
	//Renderer->CreateFBXAnimation("Slash_Light_L_new", "Slash_Light_L_new.FBX", { 0.01f,true });
	//AnimationName.push_back("Slash_Light_L_new");
	//
	//Renderer->CreateFBXAnimation("Slash_Light_R_new", "Slash_Light_R_new.FBX", { 0.01f,true });
	//AnimationName.push_back("Slash_Light_R_new");	
	//
	//Renderer->CreateFBXAnimation("Walk", "Walk.FBX", { 0.01f,true });
	//AnimationName.push_back("Walk");
	
}


void Player::TestInit()
{
	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}

	{
		Renderer = CreateComponent<GameEngineFBXRenderer>();
		Renderer->SetFBXMesh("Arrow.FBX", "MeshAniTexture");
		//Renderer->CreateFBXAnimation("Player_Idle", "Arrow.FBX", { 0.01f,true });
		//Renderer->ChangeAnimation("Player_Idle");

		CheckAllAnimation();
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
		GetTransform()->SetLocalRotation({90,0,0});
	}

}


void Player::Start()
{
	//init
	InitPlayer();
	TestInit();

	for (int i = 0; i < static_cast<int>(PlayerState::MAX); ++i)
	{
		PlayerStateParameter NewStatePara;
		FSMFunc[static_cast<PlayerState>(i)] = NewStatePara;
	}
	SetFSMFunc();

}

void Player::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown("PressN"))
	{
		if (index >= AnimationName.size())
		{
			index = 0;
		}
		Renderer->ChangeAnimation(AnimationName[index++]);
	}
	// 서버의 관리를 받는 오브젝트라면
	// 클라이언트의 입장에서는 
	// 상대의 패킷으로만 움직여야 한다.
	//// 2가지로 나뉘게 된다.
	//if (AnimationLoadCount < 13)
	//{
	//	return;
	//}
	//if (PlayerState::MAX == CurState)
	//{
	//	NextState = PlayerState::IDLE;
	//}
	//
	//NetControlType Type = GetControlType();
	//UpdateState(_DeltaTime);
	//TestMoveUpdate(_DeltaTime);

	//switch (Type)
	//{
	//case NetControlType::None:
	//	UserUpdate(_DeltaTime);
	//	break;
	//case NetControlType::UserControl:
	//	UserUpdate(_DeltaTime);
	//	break;
	//case NetControlType::ServerControl:
	//	ServerUpdate(_DeltaTime);
	//	break;
	//default:
	//	break;
	//}


}
//
void Player::TestMoveUpdate(float _DeltaTime)
{

	//if (true == GameEngineInput::IsPress("SpeedBoost") && m_pSpeed > 1000.f)
	//{
	//	m_pSpeed = 1000.f;
	//}
	//else
	//{
	//	m_pSpeed = 200.f;
	//}

	//if (true == GameEngineInput::IsPress("CamMoveLeft"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * m_pSpeed * _DeltaTime);
	//}
	//if (true == GameEngineInput::IsPress("CamMoveRight"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * m_pSpeed * _DeltaTime);
	//}
	//if (true == GameEngineInput::IsPress("CamMoveUp"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * m_pSpeed * _DeltaTime);
	//}
	//if (true == GameEngineInput::IsPress("CamMoveDown"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * m_pSpeed * _DeltaTime);
	//}
	//if (true == GameEngineInput::IsPress("CamMoveForward"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * m_pSpeed * _DeltaTime);
	//}
	//if (true == GameEngineInput::IsPress("CamMoveBack"))
	//{
	//	GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * m_pSpeed * _DeltaTime);
	//}


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



void Player::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		if (FSMFunc.end() == FSMFunc.find(NextState) || PlayerState::MAX == NextState)
		{
			MsgAssert("State에 해당하는 func이 생성되지 않았습니다");
		}
		if (nullptr != FSMFunc[CurState].End)
		{
			FSMFunc[CurState].End();
		}
		if (nullptr != FSMFunc[NextState].Start)
		{
			FSMFunc[NextState].Start();
		}
		CurState = NextState;
	}
	if (nullptr != FSMFunc[CurState].Update)
	{
		FSMFunc[CurState].Update(_DeltaTime);
	}
}

void Player::CheckInput(float _DeltaTime)
{

	//if (true == GameEngineInput::IsPress("PlayerRoll"))
	//{
	//	NextState = PlayerState::ROLL;
	//	return;
	//}
	//if (true == GameEngineInput::IsPress("PlayerLBUTTON"))
	//{
	//	NextState = PlayerState::BASE_ATT;
	//	return;
	//}
	//if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
	//{
	//	NextState = PlayerState::SKILL;
	//	return;
	//}
	if (true == GameEngineInput::IsPress("PlayerMBUTTON"))
	{
		NextState = PlayerState::CHARGE_ATT;
		return;
	}


	float4 Dir = float4::ZERO;
	// move
	if (true == GameEngineInput::IsPress("PlayerLeft"))
	{
		Dir += float4::LEFT; // 0 -90 0
	}
	if (true == GameEngineInput::IsPress("PlayerRight"))
	{
		Dir += float4::RIGHT; // 0 90 0

	}
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		Dir += float4::FORWARD; // 0 0 0

	}
	if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		Dir += float4::BACK; // 0 180 0
	}
	if (false == Dir.IsZero())
	{
		//NextState = PlayerState::WALK;
		Dir.Normalize();
		MoveDir = Dir;
		MoveUpdate(_DeltaTime);
		return;
	}
	NextState = PlayerState::IDLE;
}



void Player::MoveUpdate(float _DeltaTime)
{
	m_pCapsuleComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	m_pCapsuleComp->SetMoveSpeed(MoveDir * m_pSpeed/* * _DeltaTime*/);


	float4 Rot = float4::ZERO;
	Rot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, MoveDir);
	m_pCapsuleComp->SetRotation(-Rot);

}


void Player::UserUpdate(float _DeltaTime)
{
}

void Player::ServerUpdate(float _DeltaTime)
{
}