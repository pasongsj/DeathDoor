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

void Player::TestInit()
{
	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}

	{
		Renderer = CreateComponent<GameEngineFBXRenderer>();
		Renderer->SetFBXMesh("player.FBX", "MeshAniTexture");

		Time.Reset();

		Renderer->CreateFBXAnimation("Player_Idle", "Player_Idle.FBX");
		AnimationName.push_back("Player_Idle");


		Renderer->CreateFBXAnimation("Player_Walk_S", "Player_Walk_S.FBX"); // 걷기
		AnimationName.push_back("Player_Walk_S");


		//Renderer->CreateFBXAnimation("Player_Roll", "Player_Roll.FBX");
		//AnimationName.push_back("Player_Roll");
		//
		//
		////	Renderer->CreateFBXAnimation("Player_Idle2", "Player_Idle.FBX");
		////AnimationName.push_back("Player_Idle2");
		//
		//Renderer->CreateFBXAnimation("Player_Att_Left", "Player_Att_Left.FBX");
		//AnimationName.push_back("Player_Att_Left");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Att_R", "Player_Att_R.FBX");
		//AnimationName.push_back("Player_Att_R");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Att1", "Player_Att1.FBX"); //특수무기??
		//AnimationName.push_back("Player_Att1");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Att2", "Player_Att2.FBX");
		//AnimationName.push_back("Player_Att2");
		//
		//
		//Renderer->CreateFBXAnimation("Player_HitBack", "Player_HitBack.FBX"); // 피격
		//AnimationName.push_back("Player_HitBack");
		//
		//
		//Renderer->CreateFBXAnimation("Player_HitIdle", "Player_HitIdle.FBX");
		//AnimationName.push_back("Player_HitIdle");
		//
		//
		//Renderer->CreateFBXAnimation("Player_SlideAtt", "Player_SlideAtt.FBX"); // 슬라이드 공격
		//AnimationName.push_back("Player_SlideAtt");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Arrow", "Player_Arrow.FBX"); // 스킬 - 화살
		//AnimationName.push_back("Player_Arrow");
		//
		//
		//Renderer->CreateFBXAnimation("Player_Magic", "Player_Magic.FBX"); // 스킬 - 화살
		//AnimationName.push_back("Player_Magic");
		//
		////AnimationName.push_back("Player_Magic");
	}
	{
		float4 scale = Renderer->GetMeshScale();
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();


		if (GetLevel()->DynamicThis<PhysXTestLevel>() != nullptr)
		{
			std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();


			m_pCapsuleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
			m_pCapsuleComp->CreatePhysXActors(pLevel->GetScene(), pLevel->GetPhysics(), vscale);
		}
	}
	{
		GetTransform()->SetLocalScale(float4::ONE * 30.0f);
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
	// 서버의 관리를 받는 오브젝트라면
	// 클라이언트의 입장에서는 
	// 상대의 패킷으로만 움직여야 한다.
	//// 2가지로 나뉘게 된다.
	//if (AnimationLoadCount < 13)
	//{
	//	return;
	//}
	if (PlayerState::MAX == CurState)
	{
		float Check0 = Time.TimeCheck();
		NextState = PlayerState::IDLE;
	}

	NetControlType Type = GetControlType();
	UpdateState(_DeltaTime);
	TestMoveUpdate(_DeltaTime);

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
	//if (true == GameEngineInput::IsDown("PressN"))
	//{
	//	if (index >= AnimationName.size())
	//	{
	//		index = 0;
	//	}
	//	Renderer->ChangeAnimation(AnimationName[index++]);
	//}
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

	if (true == GameEngineInput::IsPress("PlayerRoll"))
	{
		NextState = PlayerState::ROLL;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerLBUTTON"))
	{
		NextState = PlayerState::BASE_ATT;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
	{
		NextState = PlayerState::SKILL;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerMBUTTON"))
	{
		NextState = PlayerState::CHARGE_ATT;
		return;
	}


	float4 Dir = float4::ZERO;
	float4 Rot = float4::ZERO;
	// move
	if (true == GameEngineInput::IsPress("PlayerLeft"))
	{
		Dir += GetTransform()->GetWorldLeftVector(); // 0 -90 0
	}
	if (true == GameEngineInput::IsPress("PlayerRight"))
	{
		Dir += GetTransform()->GetWorldRightVector(); // 0 90 0

	}
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		Dir += GetTransform()->GetWorldForwardVector(); // 0 0 0

	}
	if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		Dir += GetTransform()->GetWorldBackVector(); // 0 180 0
	}
	if (false == Dir.IsZero())
	{
		NextState = PlayerState::WALK;
		Dir.Normalize();
		MoveDir = Dir;
		MoveUpdate(_DeltaTime);
		return;
	}

}



void Player::MoveUpdate(float _DeltaTime)
{
	m_pCapsuleComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	m_pCapsuleComp->SetMoveSpeed(MoveDir * m_pSpeed/* * _DeltaTime*/);

}


void Player::UserUpdate(float _DeltaTime)
{
}

void Player::ServerUpdate(float _DeltaTime)
{
}