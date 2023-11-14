#include "PrecompileHeader.h"
#include "Player.h"
#include "ContentFBXRenderer.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXTestLevel.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"

#include "DustParticle.h"
#include "ContentLevel.h"

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
	InitPlayerAnimation();

	// physx
	{

		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PLAYER_PHYSX_SCALE);
		//m_pCapsuleComp->SetDynamicPivot(float4::BACK * 10.0f);
		// lever 충돌테스트 
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::PlayerDynamic);
	}
	m_pCapsuleComp->SetWorldPosWithParent(float4{1000.0f, 500.0f, 0.0f},float4::ZERO);

	SetFSMFunc();
	Renderer->ChangeAnimation("IDLE0");
	Renderer->SetGlowToUnit(0, 1);
	Renderer->SetUnitColor(0, 1, { 0.95f, 0.20f, 0.25f }, 2.0f);
	BonePivot = CreateComponent<GameEngineComponent>();
}

void Player::SpawnPosUpdate(float _DeltaTime)
{
	//PosInter -= _DeltaTime;
	//if ((true == respawnPos.empty() || PosInter < 0.0f) &&
	//	GetTransform()->GetWorldPosition().Size() > 1 &&
	//	GetCurState< PlayerState>() != PlayerState::CLIMB &&
	//	GetCurState< PlayerState>() != PlayerState::FALLING)
	//{
	//	if (respawnPos.size() >= 10)
	//	{
	//		respawnPos.pop_back();
	//	}
	//	respawnPos.push_front(GetTransform()->GetWorldPosition());
	//	PosInter = 2.0f;
	//}
}


void Player::Update(float _DeltaTime)
{
	//SpawnPosUpdate(_DeltaTime);
	DirectionUpdate(_DeltaTime); // 플레이어 방향 업데이트
	DefaultPhysX();
	FSMObjectBase::Update(_DeltaTime);


	// input 사다리타기 추후 trigger로 변경할 예정
	if (true == GameEngineInput::IsDown("PressN"))
	{
		if (PlayerState::IDLE == GetCurState<PlayerState>())
		{
			SetNextState(PlayerState::CLIMB);
		}
		else
		{
			SetNextState(PlayerState::IDLE);
		}
	}
	// state와 상관없이 스킬 변경 가능
	if (PlayerState::SKILL != GetCurState<PlayerState>())
	{
		SetSkill();
	}


	StackDuration -= _DeltaTime;
	if (StackDuration < 0.0f)
	{
		AttackStack = 0;
	}

	CameraUpdate(_DeltaTime);

	PlayerState Checker = GetCurState<PlayerState>();
	// test
	float4 MyPos = GetTransform()->GetWorldPosition();
	
}

void Player::CameraUpdate(float _DeltaTime)
{
	const float4 m_CameraRot = float4{ 55 , 0 , 0 };
	float Camheight = 1500.0f;
	std::shared_ptr<GameEngineCamera> MainCam = GetLevel()->GetMainCamera();
	if (GetCurState<PlayerState>() == PlayerState::SKILL)
	{
		Camheight = 1800.0f;
	}
	if (CameraControl == true && false == MainCam->IsFreeCamera())
	{
		float4 CurCamPos = MainCam->GetTransform()->GetWorldPosition();
		float4 CurCamRot = MainCam->GetTransform()->GetWorldRotation();


		float4 NextCamPos = GetTransform()->GetWorldPosition();
		NextCamPos.y += Camheight; // 카메라 높이

		float4 xzPos = float4::FORWARD * Camheight * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad); //xz연산
		xzPos.RotaitonYDeg(m_CameraRot.y);
		NextCamPos -= xzPos;
		MainCam->GetTransform()->SetWorldPosition(float4::LerpClamp(CurCamPos, NextCamPos, _DeltaTime * 2));
		MainCam->GetTransform()->SetWorldRotation(float4::LerpClamp(CurCamRot, m_CameraRot, _DeltaTime *0.5f));
	}
}



void Player::CheckDirInput(float _DeltaTime)
{
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
		//DirectionUpdate(_DeltaTime);
		MoveDir = Dir.NormalizeReturn();
		MoveUpdate(PLAYER_MOVE_SPEED);
	}
	else // 방향 입력이 없다면 IDLE
	{
		if (false == GetStateChecker() && GetCurState<PlayerState>() == PlayerState::WALK)
		{
			SetStateCheckerOn();
			//StateChecker = true;
			return;
		}
		else
		{
			SetNextState(PlayerState::IDLE);
		}
	}
}

void Player::CheckStateInput(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PlayerRoll")) // roll antmation inter이 필요함
	{
		SetNextState(PlayerState::ROLL);
	}
	else if (true == GameEngineInput::IsPress("PlayerLBUTTON"))
	{
		SetNextState(PlayerState::BASIC_ATT);
	}
	else if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
	{
		switch (CurSkill)
		{
		case Player::PlayerSkill::ARROW:
		case Player::PlayerSkill::MAGIC:
			if (SpellCost < 1)
			{
				return;
			}
			break;
		case Player::PlayerSkill::BOMB:
			if (SpellCost < 2)
			{
				return;
			}
			break;
		case Player::PlayerSkill::HOOK:
			break;
		default:
			break;
		}
		SetNextState(PlayerState::SKILL);
	}
	else if (true == GameEngineInput::IsPress("PlayerMBUTTON"))
	{
		SetNextState(PlayerState::CHARGE_ATT);
	}
	else if (true == GameEngineInput::IsPress("E"))
	{
		if (InteractData.Type == InteractionData::InteractionDataType::Ladder)
		{
			SetNextState(PlayerState::CLIMB);
		}
		else if (InteractData.Type == InteractionData::InteractionDataType::Lever)
		{
			SetNextState(PlayerState::LEVER);
		}
		else if(InteractData.Type == InteractionData::InteractionDataType::Door)
		{
			SetNextState(PlayerState::DOOR);
		}
	}
}


void Player::CheckFalling(float _DeltaTime)
{

	PosInter -= _DeltaTime;
	// Falling Check
	float4 PlayerGroundPos = GetTransform()->GetWorldPosition(); // 플레이어의 위치
	PlayerGroundPos.y += 50.0f;
	float4 CollPoint = float4::ZERO; // 충돌체크할 변수
	if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint, 2000.0f)) // 플레이어 위치에서 float4::DOWN 방향으로 2000.0f 길이만큼 체크한다.
	{
		if (GetTransform()->GetWorldPosition().y > CollPoint.y + 100.0f) // 300.0 이상 차이가 나는경우 falling state로 변경한다.
		{
			SetNextState(PlayerState::FALLING);
			return;
		}
		if ((true == respawnPos.empty() || PosInter < 0.0f))
		{
			if (false == respawnPos.empty() && respawnPos.front().XYZDistance(CollPoint) < 400.0f)
			{
				return;
			}
			if (respawnPos.size() >= 30)
			{
				respawnPos.pop_back();
			}
			respawnPos.push_front(CollPoint);
			PosInter = 0.5f;
		}
	}
	else
	{
		SetNextState(PlayerState::DROWN);

	}
}
void Player::CheckState(float _DeltaTime)
{
	if (PlayerHP <= 0)
	{
		SetNextState(PlayerState::DEAD);
		return;
	}
	StateInputDelayTime -= _DeltaTime;
	if (StateInputDelayTime > 0.0f)
	{
		return;
	}
	CheckDirInput(_DeltaTime);
	CheckStateInput(_DeltaTime);
	CheckFalling(_DeltaTime);
	CheckPlayerHit();
}



void Player::DirectionUpdate(float _DeltaTime)
{
	if (MoveDir == ForwardDir)
	{
		return;
	}
	float4 LerpDir = float4::LerpClamp(ForwardDir, MoveDir, _DeltaTime * 10.0f);

	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(PLAYER_DEFAULT_DIR, LerpDir);
	m_pCapsuleComp->SetRotation(/*PlayerInitRotation*/ -CalRot);
	ForwardDir = LerpDir;
}


void Player::MoveUpdate(float _MoveVec, float4 _Dir)
{
	if (float4::ZERONULL == _Dir)
	{
		m_pCapsuleComp->SetMoveSpeed(MoveDir * _MoveVec);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(_Dir * _MoveVec);
	}
}


void Player::DefaultPhysX()
{
	// physx
	{
		float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
		float4 CollPoint = float4::ZERO;
		if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint, 2000.0f) && PlayerState::CLIMB != GetCurState< PlayerState>())
		{
			float4 PPos = GetTransform()->GetWorldPosition();
			if (PPos.y > CollPoint.y + 40.0f)
			{
				return;
			}
		}
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

	float4 Player2DPos = GetBonePos("Weapon_L");
	Player2DPos *= CamViewProjectionMat;
	Player2DPos /= Player2DPos.w;
	Player2DPos.w = 1.0f;

	// Windows Forms to Cartesian Coordinate System
	Player2DPos -= GameEngineWindow::GetScreenSize().half();
	Player2DPos.y = -Player2DPos.y;
	Player2DPos.z = 0;

	float4 NDir = Mouse2DPos - Player2DPos;
	NDir.z = 0;
	NDir.RotationAllDeg(MainCam->GetTransform()->GetWorldRotation());
	NDir.Normalize();

	float4 Ydir = float4{ 0.0f,NDir.y,0.0f };
	Ydir.RotaitonXDeg(90.0f - MainCam->GetTransform()->GetWorldRotation().y);
	NDir += Ydir;
	NDir.y = 0;

	return  NDir;
}


float4 Player::GetBonePos(const std::string_view& _BoneName)
{
	AnimationBoneData Bone = Renderer->GetBoneData(_BoneName.data());
	BonePivot->GetTransform()->SetLocalPosition(Bone.Pos);

	return BonePivot->GetTransform()->GetWorldPosition();
}


void Player::CheckPlayerHit()
{
	if (true == PlayerTestMode)
	{
		return;
	}
	if (true == CheckCollision(PhysXFilterGroup::MonsterSkill))
	{
		if (false  == PlayerTestMode)
		{
			--PlayerHP;
		}
		if (0 >= PlayerHP)
		{
			SetNextState(PlayerState::DEAD);
		}
		else
		{
			SetNextState(PlayerState::HIT);
		}
	}
}

void Player::CreateDustParticle(float _Delta)
{
	ParticleCount += _Delta;

	if (ParticleCount >= 0.3f)
	{
		ParticleCount = 0.0f;

		std::shared_ptr<DustParticle> Particle = CreateComponent<DustParticle>();
		Particle->GetTransform()->SetParent(GetLevel()->DynamicThis<ContentLevel>()->GetPivotActor()->GetTransform());
		
		Particle->SetFadeOut(true);
		Particle->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{0.0f, 50.0f, -10.0f});
		Particle->GetTransform()->SetWorldScale({ 40.0f, 40.0f });
	}
}