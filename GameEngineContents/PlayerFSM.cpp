#include "PreCompileHeader.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "PlayerDefinition.h"



#include "AttackBase.h"
#include "PlayerAttackBasic.h"
#include "PlayerAttackMagic.h"
#include "PlayerAttackArrow.h"
#include "PlayerAttackBomb.h"


#include "PlayerBow.h"
#include "PlayerAttackTrail.h"


void Player::SetFSMFunc()
{
	InitFSM(PlayerState::MAX);



	//	IDLE,// Idle_0, Idle_1
	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
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
				if (false == GetStateChecker())
				{
					Renderer->ChangeAnimation("IDLE1");

				}
				else
				{
					Renderer->ChangeAnimation("IDLE0");

				}
				SetStateChecker(!GetStateChecker());
				//StateChecker = !StateChecker;
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
			if (true == GetStateChecker())
			{
				Renderer->ChangeAnimation("WALK");
				MoveUpdate(PLAYER_WALK_SPEED);
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
			//MoveUpdate(0.0f);

		}
	);


	//SKILL	// 우클릭 Arrow, Arrow_bomb, Arrow_magic, Hookshot, Hookshot_fly
	SetFSM(PlayerState::SKILL,
		[this]
		{
			MoveDir = GetMousDirection();

			switch (CurSkill)
			{
			case Player::PlayerSkill::ARROW:
			{
				Renderer->ChangeAnimation("ARROW");
				//bow
				WeaponActor = GetLevel()->CreateActor<PlayerBow>();
				float4 BowPos = GetBonePos("Weapon_L");
				WeaponActor->SetTrans(BowPos, GetTransform()->GetLocalRotation());
				//arrow
				AttackActor = GetLevel()->CreateActor<PlayerAttackArrow>();
				float4 ArrowPos = GetBonePos("Weapon_L");
				AttackActor->SetTrans(MoveDir, ArrowPos);
				break;
			}
			case Player::PlayerSkill::MAGIC:
			{
				Renderer->ChangeAnimation("MAGIC");
				AttackActor = GetLevel()->CreateActor<PlayerAttackMagic>();
				float4 MagicPos = GetBonePos("Weapon_R");
				AttackActor->SetTrans(MoveDir, MagicPos);
				break;
			}
			case Player::PlayerSkill::BOMB:
			{
				Renderer->ChangeAnimation("BOMB");
				AttackActor = GetLevel()->CreateActor<PlayerAttackBomb>();
				float4 BombPos = (GetBonePos("Weapon_R") + GetBonePos("Weapon_L")) * 0.5f;
				AttackActor->SetTrans(MoveDir, BombPos);
				break;
			}
			case Player::PlayerSkill::HOOK:
				Renderer->ChangeAnimation("HOOK");
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
			//MoveUpdate(0.0f);
		},
		[this](float Delta) // update
		{
			//StateDuration += Delta;
			if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
			{
				if (nullptr != WeaponActor)
				{
					float4 BowPos = GetBonePos("Weapon_L");
					WeaponActor->SetTrans(BowPos, GetTransform()->GetLocalRotation());
				}
				// 마우스 방향을 바라보도록 함
				MoveDir = GetMousDirection();
				float4 SkillPos;

				switch (CurSkill)
				{
				case Player::PlayerSkill::ARROW:
					SkillPos = GetBonePos("Weapon_L");
					break;
				case Player::PlayerSkill::MAGIC:
					SkillPos = GetBonePos("Weapon_R");
					break;
				case Player::PlayerSkill::BOMB:
					SkillPos = (GetBonePos("Weapon_R") + GetBonePos("Weapon_L")) * 0.5f/*+ float4{0.0f, 10.0f,0.0f}*/;
					break;
				case Player::PlayerSkill::HOOK:
					SkillPos = GetBonePos("Weapon_R");
					break;
				case Player::PlayerSkill::MAX:
					break;
				default:
					break;
				}
				AttackActor->SetTrans(ForwardDir, SkillPos);
			}
			else
			{
				if (nullptr != AttackActor)
				{
					AttackActor->SetShoot();
					AttackActor = nullptr;
				}
				if (nullptr != WeaponActor)
				{
					WeaponActor->Death();
					WeaponActor = nullptr;
				}
				SetNextState(PlayerState::IDLE);
			}
		},
		[this]
		{
			if (true == PlayerTestMode)
			{
				return;
			}
			switch (CurSkill)
			{
			case Player::PlayerSkill::ARROW:
			case Player::PlayerSkill::MAGIC:
				SpellCost--;
				break;
			case Player::PlayerSkill::BOMB:
				SpellCost -= 2;
				break;
			case Player::PlayerSkill::HOOK:
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
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

	//BASIC_ATT	// 좌클릭 Slash_Light_L_new, Slash_Light_R_new
	SetFSM(PlayerState::BASIC_ATT,
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

			// 마우스 방향을 바라보도록 함
			MoveDir = GetMousDirection();
			StackDuration = 0.55f;
			if (++AttackStack >= 3)
			{
				StateInputDelayTime = 0.25f;
			}

			{// base attack range
				AttackActor = GetLevel()->CreateActor<PlayerAttackBasic>();
				float4 AttackPos = GetTransform()->GetWorldPosition() + MoveDir * 200.0f + float4{ 0.0f,50.0f,0.0f };
				AttackActor->SetTrans(float4::ONE, AttackPos);
			}
			
			{
				//attack trail
				std::shared_ptr< PlayerAttackTrail> Trail = GetLevel()->CreateActor< PlayerAttackTrail>();
				if (true == isChargeAttack)
				{
					Trail->CreateTrail(MoveDir, GetTransform()->GetWorldPosition(), isRightAttack,false);
				}
				else
				{
					Trail->CreateTrail(MoveDir, GetTransform()->GetWorldPosition(), isRightAttack, true);
				}

			}
		},
		[this](float Delta)
		{
			MoveUpdate(PLAYER_ATT_MOVE_SPEED);
			if (true == Renderer->IsAnimationEnd())
			{
				//StateInputDelayTime = 0.1f;
				SetNextState(PlayerState::IDLE);
				AttackActor->Death();
				AttackActor = nullptr;
			}
		},
		[this]
		{
			//AttackRange->Off();
			isChargeAttack = false;
		}
	); 


	//ROLL	// 스페이스바 Roll, Roll_slash
	// Roll 하는 동안 무적상태
	SetFSM(PlayerState::ROLL,
		[this]
		{
			Renderer->ChangeAnimation("ROLL");

			// Player의 Speed를 초기화한다.
			//MoveUpdate(0.0f);


		},
		[this](float Delta)
		{
			MoveUpdate(PLAYER_ROLL_SPEED);

			if (true == GameEngineInput::IsDown("PlayerMBUTTON"))
			{
				SetStateCheckerOn();
			}
			if (true == Renderer->IsAnimationEnd())
			{
				if (true == GetStateChecker())
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
			//MoveUpdate(0.0f);
		}
	); 


	//ROLL_ATT	// 스페이스바+휠클릭 Charge_slam_overhead, Roll_slash_end
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


	// CHARGE_ATT// 휠클릭 Charge_slash_L, Charge_slash_R
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
			//MoveUpdate(0.0f);
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
				SetNextState(PlayerState::BASIC_ATT);
			}
		},
		[this]
		{
			isChargeAttack = true;
			 
		}
	); 


	//HIT  	// 공격당함 Hit_back, Hit_idle,Hit_Recover
	SetFSM(PlayerState::HIT,
		[this]
		{
			Renderer->ChangeAnimation("HIT_BACK");
		},
		[this](float Delta)
		{
			if (false == GetStateChecker() && true == Renderer->IsAnimationEnd())
			{
				Renderer->ChangeAnimation("HIT_IDLE");
				SetStateCheckerOn();
			}
			if (true == GetStateChecker() && GetStateDuration() > PLAYER_HIT_IDLE_TIME)
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
			StateInputDelayTime = 0.2f;
		}
	); 


	//CLIMB	// 사다리 Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	SetFSM(PlayerState::CLIMB,
		[this]
		{
			Renderer->ChangeAnimation("CLIMBING_LADDER");
			Renderer->PauseOn();

			m_pCapsuleComp->TurnOffGravity(); 
		},
		[this](float Delta)
		{
			// 땅에 or 사다리 끝에 도달해였는지 체크하는 함수
			CheckClimbInput(Delta);
		},
		[this]
		{
				m_pCapsuleComp->TurnOnGravity();
				Renderer->PauseOff(); 
		}
	); 

	
	//LEVER // 레버를 누름 Push_Lever
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
			}
		},
		[this]
		{
		}
	); 


	//ITEM
	// 아이템을 얻음 GetItem
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
			}
		},
		[this]
		{
		}
	); 



	//DEAD
	// 피격으로 인한 사망 Dead
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
	// 익사 Drown
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
	// 높이가 차가 있을 때 Falling, Land
	SetFSM(PlayerState::FALLING,
		[this]
		{
			Renderer->ChangeAnimation("FALLING");
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
			if (false == GetStateChecker())
			{
				float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
				PlayerGroundPos.y += 50.0f; // 피직스 컴포넌트 중력값으로 보정되기 전 위치가 측정되는 오류 해결
				float4 CollPoint = float4::ZERO;
				if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint, 2000.0f))
				{
					if (CollPoint.y + 20.0f > GetTransform()->GetWorldPosition().y)// 땅에 도달하였는지 체크
					{
						Renderer->ChangeAnimation("LAND");
						SetStateCheckerOn();
						//SetNextState(PlayerState::IDLE);
						return;
					}
				}
			}
			else if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
				return;
			}

		},
		[this]
		{
		}
	); 

}


void Player::CheckClimbInput(float _DeltaTime)
{
	// 사다리 Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		Renderer->ChangeAnimation("Climbing_ladder");
		Renderer->PauseOff();
		MoveUpdate(PLAYER_CLIMB_SPEED, float4::UP);
		//m_pCapsuleComp->SetMoveSpeed(float4::UP * PlayerMoveSpeed * ClimbSpeedRatio);
	}
	else if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
		float4 CollPoint = float4::ZERO;
		if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint))
		{
			if (CollPoint.y + 5.0f > GetTransform()->GetWorldPosition().y)
			{
				SetNextState(PlayerState::IDLE);
				return;
			}
		}

		Renderer->ChangeAnimation("Climbing_ladder_down");
		Renderer->PauseOff();
		MoveUpdate(PLAYER_CLIMB_SPEED, float4::DOWN);
		//m_pCapsuleComp->SetMoveSpeed(float4::DOWN * PlayerMoveSpeed * ClimbSpeedRatio);s

	}
	else
	{
		Renderer->PauseOn();
	}
}
