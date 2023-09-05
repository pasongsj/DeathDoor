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



void Player::Start()
{
	//init
	InitInputKey();
	InitPlayerAnimatioin();

	// physx
	//{
	//	float4 scale = Renderer->GetMeshScale();
	//	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
	//	m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
	//	if (GetLevel()->DynamicThis<PhysXTestLevel>() != nullptr)
	//	{
	//		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();
	//		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
	//		m_pCapsuleComp->CreatePhysXActors(pLevel->GetScene(), pLevel->GetPhysics(), vscale);
	//	}
	//}

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
			StateDuration = 0.0f;
			StateChecker = false;
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
		NextState = PlayerState::WALK;
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


