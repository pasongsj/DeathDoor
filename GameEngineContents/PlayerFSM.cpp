#include "PreCompileHeader.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"
#include "PlayerDefinition.h"


#define PlayerIdleTime 3.0f
#define PlayerWalkTime 0.05f
#define PlayerHitIdleTime 1.0f
#define RollSpeedRatio 3.0f
#define ClimbSpeedRatio 0.5f


void Player::SetFSMFunc()
{
	//	IDLE,// Idle_0, Idle_1
	FSMFunc[PlayerState::IDLE].Start = [this] // Idle0와 Idle1이 번갈아가며 진행됨
		{
			Renderer->ChangeAnimation("Idle_0");
		};

	FSMFunc[PlayerState::IDLE].Update = [this](float Delta)
		{
			if (Renderer->IsAnimationEnd())
			{
				if (false == StateChecker)
				{
					Renderer->ChangeAnimation("Idle_1");

				}
				else
				{
					Renderer->ChangeAnimation("Idle_0");

				}
				StateChecker = !StateChecker;
			}

			CheckInput(Delta);

		};

	FSMFunc[PlayerState::IDLE].End = [this]
		{

		};

	//WALK	// Walk, Run
	FSMFunc[PlayerState::WALK].Start = [this]
		{
			Renderer->ChangeAnimation("Run");

		};

	FSMFunc[PlayerState::WALK].Update = [this](float Delta)
		{
			//StateDuration += Delta;
			if (true == StateChecker)
			{
				Renderer->ChangeAnimation("Walk");
				if (true == Renderer->IsAnimationEnd())
				{
					NextState = PlayerState::IDLE;
				}

			}
			else
			{
				CheckInput(Delta);
			}


			//if (false == StateChecker && StateDuration > PlayerWalkTime)
			//{
			//	Renderer->ChangeAnimation("Run");
			//	StateChecker = true;
			//}

		};

	FSMFunc[PlayerState::WALK].End = [this]
		{

		};


	//SKILL	// 우클릭 Arrow, Arrow_bomb, Arrow_magic, Hookshot, Hookshot_fly
	FSMFunc[PlayerState::SKILL].Start = [this]
		{

			switch (CurSkill)
			{
			case Player::PlayerSkill::ARROW:
				Renderer->ChangeAnimation("Arrow");
				break;
			case Player::PlayerSkill::MAGIC:
				Renderer->ChangeAnimation("Arrow_magic");
				break;
			case Player::PlayerSkill::BOMB:
				Renderer->ChangeAnimation("Arrow_bomb");
				break;
			case Player::PlayerSkill::HOOK:
				Renderer->ChangeAnimation("Hookshot");
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
		};

	FSMFunc[PlayerState::SKILL].Update = [this](float Delta)
		{
			StateDuration += Delta;
			if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
			{
				// 마우스 방향을 바라보도록 함
				NextForwardDir = GetMousDirection();
				DirectionUpdate(Delta);
			}

			if (true == Renderer->IsAnimationEnd() && false == GameEngineInput::IsPress("PlayerRBUTTON"))
			{
				//switch (CurSkill)
				//{
				//case Player::PlayerSkill::ARROW:
				//	break;
				//case Player::PlayerSkill::MAGIC:
				//	break;
				//case Player::PlayerSkill::BOMB:
				//	break;
				//case Player::PlayerSkill::HOOK:
				//	break;
				//case Player::PlayerSkill::MAX:
				//	break;
				//default:
				//	break;
				//}
			}
			CheckInput(Delta);

			

		};

	FSMFunc[PlayerState::SKILL].End = [this]
		{

		};

	//HOOK_FLY	// Hookshot_fly
	FSMFunc[PlayerState::HOOK_FLY].Start = [this]
		{
			Renderer->ChangeAnimation("Hookshot_fly");

		};

	FSMFunc[PlayerState::HOOK_FLY].Update = [this](float Delta)
		{

		};

	FSMFunc[PlayerState::HOOK_FLY].End = [this]
		{

		};


	//BASE_ATT	// 좌클릭 Slash_Light_L_new, Slash_Light_R_new
	FSMFunc[PlayerState::BASE_ATT].Start = [this]
		{
			if (true == isRightAttack)
			{
				Renderer->ChangeAnimation("Slash_Light_R_new");
			}
			else
			{
				Renderer->ChangeAnimation("Slash_Light_L_new");
			}
			isRightAttack = !isRightAttack;

			// 마우스 방향을 바라보도록 함
			NextForwardDir = GetMousDirection();

		};

	FSMFunc[PlayerState::BASE_ATT].Update = [this](float Delta)
		{
			DirectionUpdate(Delta);
			MoveDir = NextForwardDir;
			MoveUpdate(Delta);

			if (true == Renderer->IsAnimationEnd())
			{
				NextState = PlayerState::IDLE;
				StateInputDelayTime = 0.3f;
			}

		};

	FSMFunc[PlayerState::BASE_ATT].End = [this]
		{

		};


	//ROLL	// 스페이스바 Roll, Roll_slash
	// Roll 하는 동안 무적상태
	FSMFunc[PlayerState::ROLL].Start = [this]
		{
			Renderer->ChangeAnimation("Roll");
			//StateDuration = 2.0f;
			mButton = false;
		};

	FSMFunc[PlayerState::ROLL].Update = [this](float Delta)
		{
			m_pCapsuleComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
			m_pCapsuleComp->SetMoveSpeed(MoveDir * MoveSpeed * RollSpeedRatio);
			if (true == GameEngineInput::IsDown("PlayerMBUTTON"))
			{
				mButton = true;
			}
			if (true == Renderer->IsAnimationEnd())
			{
				if (true == mButton)
				{
					NextState = PlayerState::ROLL_ATT;
				}
				else
				{
					StateInputDelayTime = 0.5f;
					NextState = PlayerState::IDLE;
				}
			}
		};

	FSMFunc[PlayerState::ROLL].End = [this]
		{
			
		};


	//ROLL_ATT	// 스페이스바+휠클릭 Charge_slam_overhead, Roll_slash_end
	FSMFunc[PlayerState::ROLL_ATT].Start = [this]
		{
			Renderer->ChangeAnimation("Charge_slam_overhead");

		};

	FSMFunc[PlayerState::ROLL_ATT].Update = [this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				CheckInput(Delta); // state변경
			}
		};

	FSMFunc[PlayerState::ROLL_ATT].End = [this]
		{

		};


	// CHARGE_ATT// 휠클릭 Charge_slash_L, Charge_slash_R
	FSMFunc[PlayerState::CHARGE_ATT].Start = [this]
		{
			if (true == isRightAttack)
			{
				Renderer->ChangeAnimation("Charge_slash_R");
			}
			else
			{
				Renderer->ChangeAnimation("Charge_slash_L");
			}
			//isRightAttack = !isRightAttack;
		};

	FSMFunc[PlayerState::CHARGE_ATT].Update = [this](float Delta)
		{
			if (false == GameEngineInput::IsPress("PlayerMBUTTON"))
			{
				NextState = PlayerState::BASE_ATT;
			}
		};

	FSMFunc[PlayerState::CHARGE_ATT].End = [this]
		{

		};


	//HIT  	// 공격당함 Hit_back, Hit_idle,Hit_Recover
	FSMFunc[PlayerState::HIT].Start = [this]
		{
			Renderer->ChangeAnimation("Hit_back");
		};

	FSMFunc[PlayerState::HIT].Update = [this](float Delta)
		{
			static float IdleEndTime = 0;
			StateDuration += Delta;
			if (false == StateChecker && true == Renderer->IsAnimationEnd())
			{
				Renderer->ChangeAnimation("Player_HitIdle");
				StateChecker = true;
				IdleEndTime = StateDuration + PlayerHitIdleTime;
			}
			if (true == StateChecker && StateDuration > IdleEndTime)
			{
				Renderer->ChangeAnimation("Hit_Recover");
				if (true == Renderer->IsAnimationEnd())
				{
					NextState = PlayerState::IDLE;
					//CheckInput(Delta);
				}
			}
		};

	FSMFunc[PlayerState::HIT].End = [this]
		{

		};


	//CLIMB	// 사다리 Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	FSMFunc[PlayerState::CLIMB].Start = [this]
		{
			Renderer->ChangeAnimation("Climbing_ladder");
			Renderer->PauseOn();

			m_pCapsuleComp->TurnOffGravity();
		};

	FSMFunc[PlayerState::CLIMB].Update = [this](float Delta)
		{
			CheckClimbInput(Delta);
			// 땅에 사다리 끝에 도달해였는지 체크하는 함수
			//if ()
			//{
			//
			//}
		};

	FSMFunc[PlayerState::CLIMB].End = [this]
		{
			m_pCapsuleComp->TurnOnGravity();
			Renderer->PauseOff();
		};	
	
	//LEVER // 레버를 누름 Push_Lever
	FSMFunc[PlayerState::LEVER].Start = [this]
		{
			Renderer->ChangeAnimation("Push_Lever");
		};

	FSMFunc[PlayerState::LEVER].Update = [this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::LEVER].End = [this]
		{

		};


	//ITEM
	// 아이템을 얻음 GetItem
	FSMFunc[PlayerState::ITEM].Start = [this]
		{
			Renderer->ChangeAnimation("GetItem");
		};

	FSMFunc[PlayerState::ITEM].Update = [this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::ITEM].End = [this]
		{

		};


	//DEAD
	// 피격으로 인한 사망 Dead
	FSMFunc[PlayerState::DEAD].Start = [this]
		{
			Renderer->ChangeAnimation("Dead");

		};

	FSMFunc[PlayerState::DEAD].Update = [this](float Delta)
		{

		};

	FSMFunc[PlayerState::DEAD].End = [this]
		{

		};





	//DROWN
	// 익사 Drown
	FSMFunc[PlayerState::DROWN].Start = [this]
		{
			Renderer->ChangeAnimation("Drown");

		};

	FSMFunc[PlayerState::DROWN].Update = [this](float Delta)
		{

		};

	FSMFunc[PlayerState::DROWN].End = [this]
		{

		};



	//FALLING
	// 낙사 Falling
	FSMFunc[PlayerState::FALLING].Start = [this]
		{
			Renderer->ChangeAnimation("Falling");
		};

	FSMFunc[PlayerState::FALLING].Update = [this](float Delta)
		{

		};

	FSMFunc[PlayerState::FALLING].End = [this]
		{

		};


	//FLY
	// 높이가 차가 있을 때 Fly, Land
	FSMFunc[PlayerState::FLY].Start = [this]
		{
			Renderer->ChangeAnimation("Fly");

		};

	FSMFunc[PlayerState::FLY].Update = [this](float Delta)
		{
			// 땅에 도달하였는지 체크
			//if ()
			//{
			//	Renderer->ChangeAnimation("Fly");
			//	StateChecker = true;
			//}
			//if (true == StateChecker && true == Renderer->IsAnimationEnd())
			//{
			//	CheckInput(Delta);
			//}
		};

	FSMFunc[PlayerState::FLY].End = [this]
		{

		};

}


void Player::CheckClimbInput(float _DeltaTime)
{
	// 사다리 Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		Renderer->ChangeAnimation("Climbing_ladder");
		Renderer->PauseOff();
		m_pCapsuleComp->SetMoveSpeed(float4::UP * MoveSpeed * ClimbSpeedRatio);
	}
	else if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		Renderer->ChangeAnimation("Climbing_ladder_down");
		Renderer->PauseOff();
		m_pCapsuleComp->SetMoveSpeed(float4::DOWN * MoveSpeed * ClimbSpeedRatio);

	}
	else
	{
		Renderer->PauseOn();
	}
}
