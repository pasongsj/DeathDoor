#include "PreCompileHeader.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"
#include "PlayerDefinition.h"





void Player::SetFSMFunc()
{
	InitFSM(PlayerState::MAX);



	//	IDLE,// Idle_0, Idle_1
	SetChangeFSMCallBack([this]
		{
			StateDuration = 0.0f;
			StateChecker = false;
		});

	SetFSM(PlayerState::IDLE,
		[this]
		{
			Renderer->ChangeAnimation("IDLE0");

		},
		[this](float Delta)
		{
			if (Renderer->IsAnimationEnd())
			{
				if (false == StateChecker)
				{
					Renderer->ChangeAnimation("IDLE1");

				}
				else
				{
					Renderer->ChangeAnimation("IDLE0");

				}
				StateChecker = !StateChecker;
			}
			CheckState(Delta);

		},
		[this]
		{

		}
	);


	//WALK	// Walk, Run
	SetFSM(PlayerState::WALK,
		[this]
		{
			Renderer->ChangeAnimation("RUN");


		},
		[this](float Delta)
		{
			//StateDuration += Delta;
			if (true == StateChecker)
			{
				Renderer->ChangeAnimation("WALK");
				if (true == Renderer->IsAnimationEnd())
				{
					SetNextState(PlayerState::IDLE);
				}

			}
			else
			{
				CheckState(Delta);
			}

		},
		[this]
		{

		}
	);


	//SKILL	// ��Ŭ�� Arrow, Arrow_bomb, Arrow_magic, Hookshot, Hookshot_fly
	SetFSM(PlayerState::SKILL,
		[this]
		{
			switch (CurSkill)
			{
			case Player::PlayerSkill::ARROW:
				Renderer->ChangeAnimation("ARROW");
				break;
			case Player::PlayerSkill::MAGIC:
				Renderer->ChangeAnimation("MAGIC");
				break;
			case Player::PlayerSkill::BOMB:
				Renderer->ChangeAnimation("BOMB");
				break;
			case Player::PlayerSkill::HOOK:
				Renderer->ChangeAnimation("HOOK");
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
		},
		[this](float Delta)
		{
			StateDuration += Delta;
			if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
			{
				// ���콺 ������ �ٶ󺸵��� ��
				MoveDir = GetMousDirection();
			}
			else
			{
				SetNextState(PlayerState::IDLE);
			}
			//if (/*true == Renderer->IsAnimationEnd() && */false == GameEngineInput::IsPress("PlayerRBUTTON"))
			//{
			//	//switch (CurSkill)
			//	//{
			//	//case Player::PlayerSkill::ARROW:
			//	//	break;
			//	//case Player::PlayerSkill::MAGIC:
			//	//	break;
			//	//case Player::PlayerSkill::BOMB:
			//	//	break;
			//	//case Player::PlayerSkill::HOOK:
			//	//	break;
			//	//case Player::PlayerSkill::MAX:
			//	//	break;
			//	//default:
			//	//	break;
			//	//}
			//}
			//CheckInput(Delta);
		},
		[this]
		{

		}
	); 


	//HOOK_FLY	// Hookshot_fly
	SetFSM(PlayerState::HOOK_FLY,
		[this]
		{
			Renderer->ChangeAnimation("Hookshot_fly"); 
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);

	//BASE_ATT	// ��Ŭ�� Slash_Light_L_new, Slash_Light_R_new
	SetFSM(PlayerState::BASE_ATT,
		[this]
		{
			if (true == isRightAttack)
			{
				Renderer->ChangeAnimation("SLASH_LIGHT_R");
			}
			else
			{
				Renderer->ChangeAnimation("SLASH_LIGHT_L");
			}
			isRightAttack = !isRightAttack;

			// ���콺 ������ �ٶ󺸵��� ��
			MoveDir = GetMousDirection(); 
			MoveUpdate(PlayerAttMoveSpeed);
		},
		[this](float Delta)
		{

			if (true == Renderer->IsAnimationEnd())
			{
				StateInputDelayTime = 0.1f;
				SetNextState(PlayerState::IDLE);
			}},
		[this]
		{
		}
	); 


	//ROLL	// �����̽��� Roll, Roll_slash
	// Roll �ϴ� ���� ��������
	SetFSM(PlayerState::ROLL,
		[this]
		{
			Renderer->ChangeAnimation("ROLL");
			mButton = false; 

			// Player�� Speed�� �ʱ�ȭ�Ѵ�.
			MoveUpdate(0.0f);


		},
		[this](float Delta)
		{
			MoveUpdate(PlayerMoveSpeed * RollSpeedRatio);

			if (true == GameEngineInput::IsDown("PlayerMBUTTON"))
			{
				mButton = true;
			}
			if (true == Renderer->IsAnimationEnd())
			{
				if (true == mButton)
				{
					SetNextState(PlayerState::ROLL_ATT);
				}
				else
				{
					StateInputDelayTime = 0.05f;
					SetNextState(PlayerState::IDLE);
				}
			}},
		[this]
		{
			MoveUpdate(0.0f);
		}
	); 


	//ROLL_ATT	// �����̽���+��Ŭ�� Charge_slam_overhead, Roll_slash_end
	SetFSM(PlayerState::ROLL_ATT,
		[this]
		{
			Renderer->ChangeAnimation("ROLL_SLASH_END");
		},
		[this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
			}
		},
		[this]
		{
		}
	); 


	// CHARGE_ATT// ��Ŭ�� Charge_slash_L, Charge_slash_R
	SetFSM(PlayerState::CHARGE_ATT,
		[this]
		{
			if (true == isRightAttack)
			{
				Renderer->ChangeAnimation("CHARGE_SLASH_R");
			}
			else
			{
				Renderer->ChangeAnimation("CHARGE_SLASH_L");
			}
		},
		[this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				if (true == isRightAttack)
				{
					Renderer->ChangeAnimation("CHARGE_MAX_R");
				}
				else
				{
					Renderer->ChangeAnimation("CHARGE_MAX_L");
				}
			}

			if (false == GameEngineInput::IsPress("PlayerMBUTTON"))
			{
				SetNextState(PlayerState::BASE_ATT);
			}
		},
		[this]
		{
		}
	); 


	//HIT  	// ���ݴ��� Hit_back, Hit_idle,Hit_Recover
	SetFSM(PlayerState::HIT,
		[this]
		{
			Renderer->ChangeAnimation("HIT_BACK");
		},
		[this](float Delta)
		{
			static float IdleEndTime = 0;
			StateDuration += Delta;
			if (false == StateChecker && true == Renderer->IsAnimationEnd())
			{
				Renderer->ChangeAnimation("HIT_IDLE");
				StateChecker = true;
				IdleEndTime = StateDuration + PlayerHitIdleTime;
			}
			if (true == StateChecker && StateDuration > IdleEndTime)
			{
				Renderer->ChangeAnimation("HIT_RECOVER");
				if (true == Renderer->IsAnimationEnd())
				{
					SetNextState(PlayerState::IDLE);
				}
			}
		},
		[this]
		{
		}
	); 


	//CLIMB	// ��ٸ� Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	SetFSM(PlayerState::CLIMB,
		[this]
		{
			Renderer->ChangeAnimation("CLIMBING_LADDER");
			Renderer->PauseOn();

			m_pCapsuleComp->TurnOffGravity(); 
		},
		[this](float Delta)
		{
			CheckClimbInput(Delta);
			// ���� ��ٸ� ���� �����ؿ����� üũ�ϴ� �Լ�
			//if ()
			//{
			//
			//}
		},
		[this]
		{
				m_pCapsuleComp->TurnOnGravity();
				Renderer->PauseOff(); 
		}
	); 

	
	//LEVER // ������ ���� Push_Lever
	SetFSM(PlayerState::LEVER,
		[this]
		{
			Renderer->ChangeAnimation("PUSH_LEVER");
		},
		[this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
			}},
		[this]
		{
		}
	); 


	//ITEM
	// �������� ���� GetItem
	SetFSM(PlayerState::ITEM,
		[this]
		{
			Renderer->ChangeAnimation("GETITEM");
		},
		[this](float Delta)
		{
			if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
			}},
		[this]
		{
		}
	); 



	//DEAD
	// �ǰ����� ���� ��� Dead
	SetFSM(PlayerState::DEAD,
		[this]
		{
			Renderer->ChangeAnimation("DEAD");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	); 


	//DROWN
	// �ͻ� Drown
	SetFSM(PlayerState::DROWN,
		[this]
		{
			Renderer->ChangeAnimation("DROWN");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	); 





	//FALLING
	// ���̰� ���� ���� �� Falling, Land
	SetFSM(PlayerState::FALLING,
		[this]
		{
			Renderer->ChangeAnimation("FALLING");
		},
		[this](float Delta)
		{
			float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
			//PlayerGroundPos.y -= 2.0f;
			float4 CollPoint = float4::ZERO;
			if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint, 2000.0f))
			{
				float4 CPos = GetTransform()->GetWorldPosition();
				
				if (CollPoint.y + 10.0f > CPos.y)// ���� �����Ͽ����� üũ
				{
					SetNextState(PlayerState::IDLE);
					return;
				}
			}

		},
		[this]
		{
		}
	); 

}


void Player::CheckClimbInput(float _DeltaTime)
{
	// ��ٸ� Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		Renderer->ChangeAnimation("Climbing_ladder");
		Renderer->PauseOff();
		m_pCapsuleComp->SetMoveSpeed(float4::UP * PlayerMoveSpeed * ClimbSpeedRatio);
	}
	else if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
		PlayerGroundPos.y = -1000.0f;
		float4 CollPoint = float4::ZERO;
		if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::UP, CollPoint))
		{
			if (CollPoint.y + 2.0f > GetTransform()->GetWorldPosition().y)
			{
				SetNextState(PlayerState::IDLE);
				return;
			}
		}

		Renderer->ChangeAnimation("Climbing_ladder_down");
		Renderer->PauseOff();
		m_pCapsuleComp->SetMoveSpeed(float4::DOWN * PlayerMoveSpeed * ClimbSpeedRatio);

	}
	else
	{
		Renderer->PauseOn();
	}
}
