#include "PreCompileHeader.h"
#include <GameEnginePlatform/GameEngineSound.h>
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
#include "PhysXBoxComponent.h"

#include "OfficeLevel.h"



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
			if (true ==  StateSound.IsValid())
			{
				StateSound.Stop();
			}
			StateSound = GameEngineSound::Play("Player_StepGround.mp3");
			StateSound.SetLoop();
		},
		[this](float Delta)
		{
			//StateDuration += Delta;
			if (true == GetStateChecker())
			{
				Renderer->ChangeAnimation("WALK");
				StateSound.Stop();
				MoveUpdate(PLAYER_WALK_SPEED);

				if (true == Renderer->IsAnimationEnd())
				{
					SetNextState(PlayerState::IDLE);
				}

			}
			else
			{
				CheckState(Delta);
				CreateDustParticle(Delta);
			}

		},
		[this]
		{
			if (true == StateSound.IsValid())
			{
				StateSound.Stop();
			}
			StateSound = nullptr;
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
				// Animation
				Renderer->ChangeAnimation("ARROW");

				float4 ArrowPos = GetBonePos("Weapon_L");
				// bow
				WeaponActor = GetLevel()->CreateActor<PlayerBow>();
				WeaponActor->SetTrans(ArrowPos, GetTransform()->GetLocalRotation());
				// arrow
				AttackActor = GetLevel()->CreateActor<PlayerAttackArrow>();
				AttackActor->SetTrans(MoveDir, ArrowPos);
				StateSound = GameEngineSound::Play("Player_ArrowCharge.mp3");
				break;
			}
			case Player::PlayerSkill::MAGIC:
			{
				// Animation
				Renderer->ChangeAnimation("MAGIC");

				float4 MagicPos = GetBonePos("Weapon_R");
				AttackActor = GetLevel()->CreateActor<PlayerAttackMagic>();
				AttackActor->SetTrans(MoveDir, MagicPos);
				StateSound = GameEngineSound::Play("Player_MagicReady.mp3");
				break;
			}
			case Player::PlayerSkill::BOMB:
			{
				// Animation
				Renderer->ChangeAnimation("BOMB");

				float4 BombPos = (GetBonePos("Weapon_R") + GetBonePos("Weapon_L")) * 0.5f;
				AttackActor = GetLevel()->CreateActor<PlayerAttackBomb>();
				AttackActor->SetTrans(MoveDir, BombPos);
				StateSound = GameEngineSound::Play("Player_BombReady.mp3");
				break;
			}
			case Player::PlayerSkill::HOOK:
				// Animation
				Renderer->ChangeAnimation("HOOK");
				break;
			case Player::PlayerSkill::MAX:
				break;
			default:
				break;
			}
	
		},
		[this](float Delta) // update
		{
			if (true == GameEngineInput::IsPress("PlayerRBUTTON"))
			{
				// 마우스 방향을 바라보도록 함
				MoveDir = GetMousDirection();
				float4 SkillBonePos;
				switch (CurSkill)
				{
				case Player::PlayerSkill::ARROW:
					SkillBonePos = GetBonePos("Weapon_L");
					if (nullptr != WeaponActor)
					{
						WeaponActor->SetTrans(SkillBonePos, GetTransform()->GetLocalRotation());
					}
					break;
				case Player::PlayerSkill::MAGIC:
					SkillBonePos = GetBonePos("Weapon_R");
					break;
				case Player::PlayerSkill::BOMB:
					SkillBonePos = (GetBonePos("Weapon_R") + GetBonePos("Weapon_L")) * 0.5f/*+ float4{0.0f, 10.0f,0.0f}*/;
					break;
				case Player::PlayerSkill::HOOK:
					SkillBonePos = GetBonePos("Weapon_R");
					break;
				case Player::PlayerSkill::MAX:
					break;
				default:
					break;
				}
				if (nullptr != AttackActor)
				{
					AttackActor->SetTrans(ForwardDir, SkillBonePos); // 터짐
				}
			}
			else
			{
				if (true == Renderer->IsAnimationEnd())
				{
					StateSound.Stop();
					AttackActor->SetShoot();
					switch (CurSkill)
					{
					case Player::PlayerSkill::ARROW:
						GameEngineSound::Play("Player_ArrowFire.mp3");
						break;
					case Player::PlayerSkill::MAGIC:
						GameEngineSound::Play("Player_MagicFire.mp3");
						break;
					case Player::PlayerSkill::BOMB:
						GameEngineSound::Play("Player_BombThrow.mp3");
						break;
					default:
						break;
					}

				}
				else
				{
					AttackActor->GameEngineObjectBase::Death();
				}
				if (nullptr != WeaponActor)
				{
					WeaponActor->Death();
					WeaponActor = nullptr;
				}
				AttackActor = nullptr;
				SetNextState(PlayerState::IDLE);
			}
			
		},
		[this]
		{
			if (true == StateSound.IsValid())
			{
				StateSound.Stop();
			}
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
			StackDuration = 0.8f;
			if (false == isChargeAttack)
			{
				std::vector<std::string> BasicAttackSound = { "Player_Attack.mp3","Player_Attack3.mp3","Player_Attack2.mp3" };
				GameEngineSound::Play(BasicAttackSound[AttackStack]);
			}
			else
			{
				GameEngineSound::Play("Player_StrongAtk.mp3");

			}
			if (++AttackStack >= 3)
			{
				StateInputDelayTime = 0.3f;
				AttackStack = 0;
			}


			{// base attack range
				AttackActor = GetLevel()->CreateActor<AttackBase>();
				float4 AttackPos = float4::ZERO;
				if (false == isChargeAttack)
				{
					AttackActor->CreatePhysXAttComp<PhysXBoxComponent>(float4{ 300.0f, 300.0f, 300.0f }, PhysXFilterGroup::PlayerSkill);
					AttackPos = GetTransform()->GetWorldPosition() + MoveDir * 200.0f + float4{ 0.0f,100.0f,0.0f };
				}
				else
				{
					AttackActor->CreatePhysXAttComp<PhysXBoxComponent>(float4{ 500.0f, 300.0f, 500.0f }, PhysXFilterGroup::PlayerSkill);
					AttackPos = GetTransform()->GetWorldPosition() + MoveDir * 300.0f + float4{ 0.0f,100.0f,0.0f };
				}
				AttackActor->SetTrans(MoveDir, AttackPos);

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
			if (GetStateDuration() < 2.8f)
			{
				MoveUpdate(PLAYER_ATT_MOVE_SPEED);
			}
			if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
				if (nullptr != AttackActor)
				{
					AttackActor->Death();
				}
				AttackActor = nullptr;
			}
		},
		[this]
		{
			if (nullptr != AttackActor)
			{
				AttackActor->Death();
			}
			AttackActor = nullptr;
			isChargeAttack = false;
		}
	); 


	//ROLL	// 스페이스바 Roll, Roll_slash
	// Roll 하는 동안 무적상태
	SetFSM(PlayerState::ROLL,
		[this]
		{
			Renderer->ChangeAnimation("ROLL");
			std::vector<std::string> Rollsound = { "Player_Roll.mp3","Player_Roll1.mp3","Player_Roll2.mp3" };
			GameEngineSound::Play(Rollsound);

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
			GameEngineSound::Play("Player_RollAttack.mp3");
			Renderer->ChangeAnimation("ROLL_SLASH_END");
			AttackActor = GetLevel()->CreateActor<AttackBase>();
			AttackActor->CreatePhysXAttComp<PhysXBoxComponent>(float4{300.0f, 100.0f, 100.0f }, PhysXFilterGroup::PlayerSkill);
			float4 AttackPos = GetTransform()->GetWorldPosition() + MoveDir * 200.0f + float4{ 0.0f,50.0f,0.0f };
			AttackActor->SetTrans(MoveDir, AttackPos);
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
			AttackActor->Death();
			AttackActor = nullptr;
		}
	); 


	// CHARGE_ATT// 휠클릭 Charge_slash_L, Charge_slash_R
	SetFSM(PlayerState::CHARGE_ATT,
		[this]
		{
			GameEngineSound::Play("Player_Charge.mp3");
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
			if (true == Renderer->IsAnimationEnd()&& false == GetStateChecker())
			{
				if (true == isRightAttack)
				{
					Renderer->ChangeAnimation("CHARGE_MAX_R");
				}
				else
				{
					Renderer->ChangeAnimation("CHARGE_MAX_L");
				}
				GameEngineSound::Play("Player_ChargeAttackReady.mp3");
				SetStateCheckerOn();
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
			GameEngineSound::Play("Player_GetDamage.mp3");
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
			m_pCapsuleComp->SetWorldPosWithParent(InteractData.Pos);
			MoveDir = InteractData.Dir; 
			m_pCapsuleComp->RigidSwitch(false);
			StateSound = GameEngineSound::Play("Player_StepLadderPrev.mp3");
		},
		[this](float Delta)
		{
			if (false == GetStateChecker() && GetStateDuration() > 1.0f)
			{
				StateSound = GameEngineSound::Play("Player_StepLadder.mp3");
				StateSound.SetLoop();
				StateSound.SetPause(true);
				SetStateCheckerOn();
			}
			// 땅에 or 사다리 끝에 도달해였는지 체크하는 함수
			CheckClimbInput(Delta);
		},
		[this]
		{
			
			m_pCapsuleComp->TurnOnGravity();
			Renderer->PauseOff(); 
			InteractData.Type = InteractionData::InteractionDataType::None;
			InteractData.Pos = float4::ZERONULL;
			InteractData.Dir = float4::ZERONULL;
			m_pCapsuleComp->RigidSwitch(true);
			if (true == StateSound.IsValid())
			{
				StateSound.Stop();
			}
			StateSound = nullptr;
		}
	); 

	SetFSM(PlayerState::CLIMB_TOP,
		[this]
		{
			Renderer->ChangeAnimation("CLIMBING_OFF_LADDER_TOP");
			m_pCapsuleComp->TurnOffGravity();

		},
		[this](float Delta)
		{
			MoveUpdate(PLAYER_CLIMB_SPEED, float4::UP + MoveDir);
			if (true == Renderer->IsAnimationEnd())
			{
				SetNextState(PlayerState::IDLE);
			}
		},
		[this]
		{
			m_pCapsuleComp->TurnOnGravity();
		}
	);


	
	//LEVER // 레버를 누름 Push_Lever
	SetFSM(PlayerState::LEVER,
		[this]
		{
			m_pCapsuleComp->SetWorldPosWithParent(InteractData.Pos);
			MoveDir = InteractData.Dir;
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
			InteractData.Type = InteractionData::InteractionDataType::None;
			InteractData.Pos = float4::ZERONULL;
			InteractData.Dir = float4::ZERONULL;
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



	SetFSM(PlayerState::DOOR,
		[this]
		{
			Renderer->ChangeAnimation("WALK");
			MoveDir = InteractData.Dir;
			m_pCapsuleComp->SetWorldPosWithParent(InteractData.Pos);
		},
		[this](float Delta)
		{
			MoveUpdate(PLAYER_WALK_SPEED);
			if (GetStateDuration() > 1.5f)
			{
				SetNextState(PlayerState::IDLE);
			}
		},
		[this]
		{
			InteractData.Type = InteractionData::InteractionDataType::None;
			InteractData.Pos = float4::ZERONULL;
			InteractData.Dir = float4::ZERONULL;
		}
	); 

	//DEAD
	// 피격으로 인한 사망 Dead
	SetFSM(PlayerState::DEAD,
		[this]
		{
			Renderer->ChangeAnimation("DEAD");
			GameEngineSound::Play("Player_Death.mp3");
		},
		[this](float Delta)
		{
			std::shared_ptr<GameEngineLevel> NextLevel = GameEngineCore::ChangeLevel("OfficeLevel");
			std::shared_ptr<OfficeLevel> Level = NextLevel->DynamicThis<OfficeLevel>();
			if (nullptr == Level)
			{
				MsgAssert("다음 레벨의 다이나믹캐스트 결과가 nullptr 입니다.");
				return;
			}

			//Level->SetPrevLevelType(PrevLevelType::FortressLevel);
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
			if (GetStateDuration() > 2.0f)
			{
				if (false == PlayerTestMode)
				{
					--PlayerHP;
				}

				if (PlayerHP <= 0)
				{
					SetNextState(PlayerState::DEAD);
					return;
				}
				else
				{
					auto it = respawnPos.begin();
					for (;it != respawnPos.end(); ++it)
					{
						float4 TempPos = (*it);
						TempPos.y += 50.0f;
				
						float4 CollPoint = float4::ZERO;
						if (true == m_pCapsuleComp->RayCast(TempPos, float4::DOWN, CollPoint))
						{
							m_pCapsuleComp->SetWorldPosWithParent(TempPos);
							SetNextState(PlayerState::IDLE);
							respawnPos.clear();
							return;
						}
					}
				}
				SetNextState(PlayerState::DEAD);
				return;
			}
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
				else
				{
					SetNextState(PlayerState::DROWN);
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
	if (true == GetStateChecker())
	{
		StateSound.SetPause(false);
	}
	if (true == GameEngineInput::IsPress("PlayerUp"))
	{
		float4 PlayerGroundPos = GetTransform()->GetWorldPosition() + (MoveDir * 50.0f);
		PlayerGroundPos.y += 50.0f;	
		float4 CollPoint = float4::ZERO;
		if (true == m_pCapsuleComp->RayCast(PlayerGroundPos, float4::DOWN, CollPoint))
		{
			if (fabsf(CollPoint.y - PlayerGroundPos.y) < 5.0f)
			{
				SetNextState(PlayerState::CLIMB_TOP);
				return;
			}
		}

		Renderer->ChangeAnimation("Climbing_ladder");
		Renderer->PauseOff();
		MoveUpdate(PLAYER_CLIMB_SPEED, float4::UP);
	}
	else if (true == GameEngineInput::IsPress("PlayerDown"))
	{
		float4 PlayerGroundPos = GetTransform()->GetWorldPosition();
		PlayerGroundPos.y += 50;
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
	}
	else
	{
		if(true == GetStateChecker())
		{
			StateSound.SetPause(true);
		}
		Renderer->PauseOn();
	}
}
