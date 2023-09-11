#include "PrecompileHeader.h"
#include "Player.h"
#include "ContentFBXRenderer.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXTestLevel.h"
#include "PhysXCapsuleComponent.h"


#define PlayerInitRotation float4{ 90,0,0 }

Player* Player::MainPlayer = nullptr;


Player::Player()
{
	//if (nullptr != MainPlayer)
	//{
	//	MainPlayer->Death();
	//	//MainPlayer = nullptr;
	//}
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
	{
		float4 scale = Renderer->GetMeshScale() * Renderer->GetTransform()->GetWorldScale() / Renderer->GetTransform()->GetLocalScale();
		// scale *= 2.0f;
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(vscale);
	}


	SetFSMFunc();
	Renderer->ChangeAnimation("Idle_0");
}

void Player::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
	if (true == GameEngineInput::IsDown("PressN"))
	{
		if (PlayerState::IDLE == GetCurState<PlayerState>())
		{
			SetNextState(PlayerState::CLIMB);
			//NextState = PlayerState::CLIMB;
		}
		else
		{
			SetNextState(PlayerState::IDLE);
			//NextState = PlayerState::IDLE;1
		}
	}
	DefaultPhysX();
	if (PlayerState::SKILL != GetCurState<PlayerState>())
	{
		SetSkill();
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

	// test
	float4 MyPos = GetTransform()->GetWorldPosition();

}


void Player::CheckInput(float _DeltaTime)
{
	

	// special state input
	StateInputDelayTime -= _DeltaTime;
	if (StateInputDelayTime > 0.0f)
	{
		return;
	}
	if (true == GameEngineInput::IsDown("PlayerRoll")) // roll antmation inter이 필요함
	{
		SetNextState(PlayerState::ROLL);
		//NextState = PlayerState::ROLL;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerLBUTTON"))
	{
		SetNextState(PlayerState::BASE_ATT);
		//NextState = PlayerState::BASE_ATT;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
	{
		SetNextState(PlayerState::SKILL);
		//NextState = PlayerState::SKILL;
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerMBUTTON"))
	{
		SetNextState(PlayerState::CHARGE_ATT);
		//NextState = PlayerState::CHARGE_ATT;
		return;
	}

	// move state input
	float4 Dir = float4::ZERO;
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

	if (false == Dir.IsZero()) //  방향 입력이 있다면
	{
		SetNextState(PlayerState::WALK);
		NextForwardDir = Dir.NormalizeReturn();
		DirectionUpdate(_DeltaTime);

		MoveDir = NextForwardDir;
		MoveUpdate(_DeltaTime);
	}
	else // 방향 입력이 없다면
	{
		if (false == StateChecker && GetCurState<PlayerState>() == PlayerState::WALK)
		{
			StateChecker = true;
			return;
		}
		else
		{
			SetNextState(PlayerState::IDLE);
		}
	}
	
}
void Player::DirectionUpdate(float _DeltaTime)
{
	if (NextForwardDir == ForwardDir)
	{
		return;
	}
	float4 LerpDir = float4::LerpClamp(ForwardDir, NextForwardDir, _DeltaTime * 10.0f);
	//float4 NextFRot = float4::LerpClamp(MoveDir, NextDir, _DeltaTime * 10.0f);

	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, LerpDir);
	m_pCapsuleComp->SetRotation(/*PlayerInitRotation*/ -CalRot);
	ForwardDir = LerpDir;
}



void Player::MoveUpdate(float _DeltaTime)
{
	m_pCapsuleComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	m_pCapsuleComp->SetMoveSpeed(MoveDir * MoveSpeed);

}


void Player::UserUpdate(float _DeltaTime)
{
}

void Player::ServerUpdate(float _DeltaTime)
{
}


void Player::DefaultPhysX()
{
	// physx
	{
		m_pCapsuleComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
		m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
	}
}


void Player::SetSkill()
{
	if (true == GameEngineInput::IsDown("PlayerSkillArrow"))
	{
		CurSkill = PlayerSkill::ARROW;
	}
	else if (true == GameEngineInput::IsDown("PlayerSkillMagic"))
	{
		CurSkill = PlayerSkill::MAGIC;
	}
	else if (true == GameEngineInput::IsDown("PlayerSkillBomb"))
	{
		CurSkill = PlayerSkill::BOMB;
	}
	else if (true == GameEngineInput::IsDown("PlayerSkillHook"))
	{
		CurSkill = PlayerSkill::HOOK;
	}
}


float4 Player::GetMousDirection()
{
	// Windows Forms to Cartesian Coordinate System
	float4 Mouse2DPos = GameEngineWindow::GetMousePosition() - GameEngineWindow::GetScreenSize().half();
	Mouse2DPos.y = -Mouse2DPos.y;

	// 3D to 2D matrix
	std::shared_ptr<GameEngineCamera> MainCam = GetLevel()->GetMainCamera();
	float4x4 CamViewProjectionMat = MainCam->GetView() * MainCam->GetProjection() * MainCam->GetViewPort();

	float4 Player2DPos = GetTransform()->GetWorldPosition() * CamViewProjectionMat;
	Player2DPos /= Player2DPos.w;
	Player2DPos.w = 1.0f;

	// Windows Forms to Cartesian Coordinate System
	Player2DPos -= GameEngineWindow::GetScreenSize().half();
	Player2DPos.y = -Player2DPos.y;


	float4 NDir = Mouse2DPos - Player2DPos;


	return  float4{ NDir.x, 0, NDir.y }.NormalizeReturn();
}
