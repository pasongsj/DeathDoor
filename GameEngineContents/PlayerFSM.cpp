#include "PreCompileHeader.h"
#include "Player.h"

//IDLE,
//WALK,
//BASE_ATT,		// 좌클릭
//ROLL,			// 스페이스바
//SLIDE_ATT,		// 스페이스바+휠클릭
//CHARGE_ATT,		// 휠클릭
//SKILL,			// 우클릭
//




void Player::SetFSMFunc()
{

	FSMFunc[PlayerState::IDLE].Start = [this]
		{
			Renderer->ChangeAnimation("Player_Idle");

		};

	FSMFunc[PlayerState::IDLE].Update = [this](float Delta)
		{
			CheckInput(Delta);
		};

	FSMFunc[PlayerState::IDLE].End = [this]
		{

		};



	FSMFunc[PlayerState::WALK].Start = [this]
		{
			Renderer->ChangeAnimation("Player_Walk_S");

			StateDuration = 0.5f;

			//float rot = MoveDir.x * 90 - (1 - MoveDir.z) * 90;
			//GetTransform()->SetLocalRotation(float4{ 0,rot,0 });
		};

	FSMFunc[PlayerState::WALK].Update = [this](float Delta)
		{
			CheckInput(Delta);
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}

		};

	FSMFunc[PlayerState::WALK].End = [this]
		{

		};



	FSMFunc[PlayerState::BASE_ATT].Start = [this]
		{
			if (true == isRightAttack)
			{
				Renderer->ChangeAnimation("Player_Att_R");
			}
			else
			{
				Renderer->ChangeAnimation("Player_Att_Left");
			}
			isRightAttack = !isRightAttack;
			StateDuration = 2.0f;
		};

	FSMFunc[PlayerState::BASE_ATT].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::BASE_ATT].End = [this]
		{

		};



	FSMFunc[PlayerState::ROLL].Start = [this]
		{
			Renderer->ChangeAnimation("Player_Roll");
			StateDuration = 2.0f;

		};

	FSMFunc[PlayerState::ROLL].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}

			if (true == GameEngineInput::IsPress("PlayerMBUTTON"))
			{
				NextState = PlayerState::SLIDE_ATT;
				return;
			}
		};

	FSMFunc[PlayerState::ROLL].End = [this]
		{

		};



	FSMFunc[PlayerState::SLIDE_ATT].Start = [this]
		{
			Renderer->ChangeAnimation("Player_SlideAtt");
			StateDuration = 2.0f;

		};

	FSMFunc[PlayerState::SLIDE_ATT].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::SLIDE_ATT].End = [this]
		{

		};



	FSMFunc[PlayerState::CHARGE_ATT].Start = [this]
		{
			StateDuration = 2.0f;
		};

	FSMFunc[PlayerState::CHARGE_ATT].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::CHARGE_ATT].End = [this]
		{

		};



	FSMFunc[PlayerState::SKILL].Start = [this]
		{
			switch (CurSkill)
			{
			case Player::PlayerSkill::ARROW:
				Renderer->ChangeAnimation("Player_Arrow");
				break;
			case Player::PlayerSkill::FIRE:
				Renderer->ChangeAnimation("Player_Magic");
				break;
			case Player::PlayerSkill::BOMB:
				break;
			case Player::PlayerSkill::HOOK:
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
			StateDuration = 2.0f;

		};

	FSMFunc[PlayerState::SKILL].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::SKILL].End = [this]
		{

		};
	


	FSMFunc[PlayerState::ATTED].Start = [this]
		{
			StateDuration = 2.0f;
		};

	FSMFunc[PlayerState::ATTED].Update = [this](float Delta)
		{
			StateDuration -= Delta;
			if (StateDuration < 0.0f)
			{
				NextState = PlayerState::IDLE;
			}
		};

	FSMFunc[PlayerState::ATTED].End = [this]
		{

		};



}
