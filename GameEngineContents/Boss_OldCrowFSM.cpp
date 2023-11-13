#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"
#include "Boss_OldCrowChain.h"
#include "Player.h"
#include "Boss_OldCrowCrowHead.h"
#include "Boss_OldCrowSmallCrow.h"
#include "Boss_OldCrowEgg.h"

#include <GameEngineBase/GameEngineRandom.h>

void Boss_OldCrow::SetFSMFUNC()
{
	InitFSM(Boss_OldCrowState::MAX);

	SetFSM(Boss_OldCrowState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (true)
			{
				SetRandomPattern();
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::DASHSTART,
		[this]
		{
			EnemyRenderer->ChangeAnimation("DashStart");
		},
		[this](float Delta)
		{
			SetLerpDirection(Delta);
			
			if (EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(Boss_OldCrowState::DASH);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::DASH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("Dash");

			m_pCapsuleComp->RigidSwitch(false);

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED;

			for (int i = 0; i < 10; i++)
			{
				CreateFeatherParticle();
			}
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * CurrentSpeed);

			TurnCheck();

			SetLerpDirection(Delta);
		},
		[this]
		{

		}
	);

	SetFSM(Boss_OldCrowState::TURN,
		[this]
		{
			EnemyRenderer->ChangeAnimation("TurnLeft");

			PlayRandomTurnSound();

			IsTurn = false;
		},
		[this](float Delta)
		{
			if (IsTurn)
			{
				SetLerpDirection(Delta * 10.0f);
			}

			if (EnemyRenderer->IsAnimationEnd())
			{
				SetNextPatternState();
			}
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);

			m_pCapsuleComp->RigidSwitch(true);
		}
	);
	
	SetFSM(Boss_OldCrowState::MEGADASHPREP,
		[this]
		{
			EnemyRenderer->ChangeAnimation("MegaDashPrep");

			StateCalTime = 0.0f; //사슬 멈추는 시간

			ChainsPivots[0]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
			ChainsPivots[0]->GetTransform()->SetWorldRotation(GetTransform()->GetWorldRotation());
			Chains[0]->OnChainEffect();

			CurrentChainSpeed = BOSS_OLDCROW_CHAINSPEED;
		},
		[this](float Delta)
		{
			//SetLerpDirection(Delta);

			StateCalTime += Delta;
			FeatherCount += Delta;
			
			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			Chains[0]->GetTransform()->AddLocalPosition(float4::FORWARD * BOSS_OLDCROW_CHAINSPEED * Delta);

			if (StateCalTime >= BOSS_OLDCROW_CREATECHAINTIME)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime >= BOSS_OLDCROW_MEGADASHPATTERNEND)
			{
				SetNextState(Boss_OldCrowState::MEGADASH);
				return;
			}


		},
		[this]
		{
			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASHPREPRANDOMPOS,
		[this]
		{
			EnemyRenderer->ChangeAnimation("MegaDashPrep");

			StateCalTime = 0.0f; //사슬 멈추는 시간

			SetMegaDashRandomPos();

			ChainsPivots[0]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
			ChainsPivots[0]->GetTransform()->SetWorldRotation(GetTransform()->GetWorldRotation());

			Chains[0]->OnChainEffect();

			CurrentChainSpeed = BOSS_OLDCROW_CHAINSPEED;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			FeatherCount += Delta;

			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			Chains[0]->GetTransform()->AddLocalPosition(float4::FORWARD * CurrentChainSpeed * Delta);

			if (StateCalTime >= BOSS_OLDCROW_CREATECHAINTIME)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime >= BOSS_OLDCROW_MEGADASHPATTERNEND)
			{
				SetNextState(Boss_OldCrowState::MEGADASH);
				return;
			}


		},
		[this]
		{
			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("MegaDash");

			ChainsPivots[0]->GetTransform()->SetParent(GetTransform());

			m_pCapsuleComp->RigidSwitch(false);

			StateCalTime = 0.0f;

			GameEngineSound::Play("OldCrow_SonicBoom2.mp3");
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			FeatherCount += Delta;

			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			m_pCapsuleComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_MEGADASHSPEED );

			if (StateCalTime >= 1.0f)
			{
				SetNextPatternState();
				return;
			}
		},
		[this]
		{
			Chains[0]->SetDefault();

			ChainsPivots[0]->GetTransform()->SetParent(nullptr);

			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);

			m_pCapsuleComp->RigidSwitch(true);

			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH2PREP,
		[this]
		{
			MegaDash2PatternTransformPivot->GetTransform()->SetWorldPosition(Player::MainPlayer->GetTransform()->GetWorldPosition());

			SettingChainPatternPivot();

			EnemyRenderer->ChangeAnimation("MegaDashPrep");
			MegaDash2PatternCount = 0; //현재 진행중인 패턴 번호

			MegaDash2PatternNumber = GameEngineRandom::MainRandom.RandomInt(0, 1);
			//MegaDash2PatternNumber = 0;


			switch (MegaDash2PatternNumber)
			{
			case 0:
				ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldPosition(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldPosition());
				ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldRotation(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());

				m_pCapsuleComp->SetWorldPosWithParent(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldPosition(), MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());
				break;
			case 1:
				ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldPosition(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldPosition());
				ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldRotation(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());

				m_pCapsuleComp->SetWorldPosWithParent(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldPosition(), MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());
				break;
			default:
				break;
			}

			Chains[MegaDash2PatternCount]->OnChainEffect();


			CurrentChainSpeed = BOSS_OLDCROW_CHAINSPEED;

			StateCalTime = 0.0f; 
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			FeatherCount += Delta;

			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			Chains[MegaDash2PatternCount]->GetTransform()->AddLocalPosition(float4::FORWARD * CurrentChainSpeed * Delta);

			if (StateCalTime >= BOSS_OLDCROW_CREATECHAINTIME)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime > BOSS_OLDCROW_MEGADASHPATTERNEND)
			{
				CurrentChainSpeed = BOSS_OLDCROW_CHAINSPEED;
				++MegaDash2PatternCount;

				if (MegaDash2PatternCount > BOSS_OLDCROW_CHAINCOUNT - 1)
				{
					SetNextState(Boss_OldCrowState::MEGADASH2);
					return;
				}
				else
				{
					StateCalTime = 0.0f;

					switch (MegaDash2PatternNumber)
					{
					case 0:
						ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldPosition(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldPosition());
						ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldRotation(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());

						break;
					case 1:
						ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldPosition(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldPosition());
						ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetWorldRotation(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());

						break;
					default:
						break;
					}

					Chains[MegaDash2PatternCount]->OnChainEffect();
				}

			}
		},
		[this]
		{
			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH2,
		[this]
		{
			EnemyRenderer->ChangeAnimation("MegaDash");

			MegaDash2PatternCount = 0;

			ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetParent(GetTransform());

			m_pCapsuleComp->RigidSwitch(false);

			GameEngineSound::Play("OldCrow_SonicBoom2.mp3");

			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			
			FeatherCount += Delta;
			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_MEGADASHSPEED);

			if (StateCalTime >= 1.0f)
			{
				StateCalTime = 0.0f;

				Chains[MegaDash2PatternCount]->SetDefault();
				ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetParent(nullptr);

				if (++MegaDash2PatternCount > BOSS_OLDCROW_CHAINCOUNT - 1)
				{
					SetNextPatternState();
					return;
				}
				else
				{
					switch (MegaDash2PatternNumber)
					{
					case 0:
						m_pCapsuleComp->SetWorldPosWithParent(MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldPosition(), MegaDash2PatternTransforms1[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());
						break;
					case 1:
						m_pCapsuleComp->SetWorldPosWithParent(MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldPosition(), MegaDash2PatternTransforms2[MegaDash2PatternCount]->GetTransform()->GetWorldRotation());
						break;
					default:
						break;
					}

					GameEngineSound::Play("OldCrow_SonicBoom2.mp3");
					ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetParent(GetTransform());
				}
			}
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);

			m_pCapsuleComp->RigidSwitch(true);

			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::JUMP,
		[this]
		{
			EnemyRenderer->ChangeAnimation("Jump");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 EnemyPos = GetTransform()->GetWorldPosition();

			float4 Position = float4::LerpClamp(EnemyPos, PlayerPos, 0.5f); //목표 지점

			TargetPos = Position;
			TargetPos.y += 1250.0f;

			JumpDir = TargetPos - EnemyPos;
			JumpDir.Normalize();

			m_pCapsuleComp->TurnOffGravity();

			StateCalTime = 0.0f;

			m_pCapsuleComp->DetachShape();
			SetDirection();

			m_pCapsuleComp->RigidSwitch(false);

			for (int i = 0; i < 15; i++)
			{
				CreateFeatherParticle();
			}

			GameEngineSound::Play("OldCrow_SonicBoom1.mp3");
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			FeatherCount += Delta;
			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}

			SetLerpDirection(Delta);

			float4 BossPos = GetTransform()->GetWorldPosition();

			float Value = BossPos.XYZDistance(TargetPos);
			//float Value2= Boss

			if (Value >= 50.0f)
			{
				m_pCapsuleComp->SetMoveSpeed(JumpDir * BOSS_OLDCROW_JUMPFORCE);
			}

			if (Value <= 50.0f && StateCalTime > 1.0f)
			{
				SetNextState(Boss_OldCrowState::SLAM);
				return;
			}

			if (StateCalTime > 2.0f)
			{
				SetNextState(Boss_OldCrowState::SLAM);
				return;
			}
		},
		[this]
		{
			FeatherCount = 0.0f;
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
			SetDirection();
		}
	);

	SetFSM(Boss_OldCrowState::SLAM,
		[this]
		{
			EnemyRenderer->ChangeAnimation("Slam");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 BossPos = GetTransform()->GetWorldPosition();

			SlamDir = PlayerPos - BossPos;
			SlamDir.Normalize();
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(SlamDir * BOSS_OLDCROW_SLAMFORCE);
			FeatherCount += Delta;
			if (FeatherCount >= 0.02f)
			{
				FeatherCount = 0.0f;

				CreateFeatherParticle();
			}
			//SetLerpDirection(Delta);

			float4 CollPoint = float4::ZERO;
			if (true == m_pCapsuleComp->RayCast(GetTransform()->GetWorldPosition(), float4::DOWN, CollPoint, 2000.0f))
			{
				if (CollPoint.y + 100.0f > GetTransform()->GetWorldPosition().y)// 땅에 도달하였는지 체크
				{
					m_pCapsuleComp->AttachShape();

					SetNextState(Boss_OldCrowState::SLAMIMPACT);
					return;
				}
			}
		},
		[this]
		{
			m_pCapsuleComp->TurnOnGravity();
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
			m_pCapsuleComp->RigidSwitch(true);
			FeatherCount = 0.0f;
		}
	);

	SetFSM(Boss_OldCrowState::SLAMIMPACT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SlamImpact");
			GameEngineSound::Play("OldCrow_Landing.mp3");

			for (int i = 0; i < 15; i++)
			{
				CreateFeatherParticle();
				GetLevel()->TimeEvent.AddEvent(0.05f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
					{
						CreateDustParticle();
					}
				);

			}
		},
		[this](float Delta)
		{
			if (EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(Boss_OldCrowState::DASH);
			}
		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::EGG,
		[this]
		{
			EnemyRenderer->ChangeAnimation("Egg");
			GameEngineSound::Play("OldCrow_EggScream.mp3");
			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			if (StateCalTime >= 4.0f)
			{
				SetNextPatternState();
			}

		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::SCREAMMINI,
		[this]
		{
			EnemyRenderer->ChangeAnimation("ScreamMini");

			StateCalBool = false; //애니메이션 상에서 True되어 true상태면 smallcrow까마귀 생성

			StateCalTime = 0.0f; //까마귀 생성
			StateCalTime2 = 0.0f;//다음패턴 체크

			StateCalFloat = GameEngineRandom::MainRandom.RandomFloat(0, 35);
			StateCalFloat *= 10.0f;

			GameEngineSound::Play("OldCrow_Scream.mp3");
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			StateCalTime2 += Delta;
			StateCalFloat += BOSS_OLDCROW_OrbitSpeed * Delta;

			if (StateCalTime2 >= 2.5f)
			{
				SetNextPatternState();
			}

			if (GetEnemyHP() <= BOSS_OLDCROW_HP / 2)  //체력이 특정 수치보다 적으면 작은 까마귀 생성
			{ 
				if (StateCalTime > 0.1f && true == StateCalBool)
				{
					std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent<GameEngineComponent>();
					BonePivot->GetTransform()->SetParent(GetTransform());
					BonePivot->GetTransform()->SetLocalPosition(float4{ 0, 10, 5 });

					float Value = 5.0f;

					float RandomXValue = GameEngineRandom::MainRandom.RandomFloat(-Value, Value);
					float RandomYValue = GameEngineRandom::MainRandom.RandomFloat(-Value, Value);
					float RandomZValue = GameEngineRandom::MainRandom.RandomFloat(-Value, Value);


					BonePivot->GetTransform()->AddLocalRotation({ -20.0f, 0.0f, 0.0f });
					BonePivot->GetTransform()->AddLocalRotation({ RandomXValue, RandomYValue, RandomZValue });

					float RandomFloat = GameEngineRandom::MainRandom.RandomFloat(-30, 30);

					std::shared_ptr<Boss_OldCrowSmallCrow> SmallCrow = GetLevel()->CreateActor<Boss_OldCrowSmallCrow>();
					SmallCrow->SetSmallCrow(BonePivot->GetTransform()->GetWorldPosition(), BonePivot->GetTransform()->GetWorldRotation(), StateCalFloat + RandomFloat, m_pCapsuleComp);

					StateCalTime = 0.0f;
				}
			}
		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::DEATHWHILERUNNING,
		[this]
		{
			EnemyRenderer->ChangeAnimation("DeathInRunning");

			GameEngineSound::Play("OldCrow_Death.mp3");

			StateCalTime = 0.0f;
			StateCalFloat = 500.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;
			StateCalFloat -= Delta * 300.0f;

			if (StateCalFloat <= 0.0f)
			{
				StateCalFloat = 0.0f;
			}

			if (StateCalTime <= 2.0f)
			{
				m_pCapsuleComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * StateCalFloat);
			}

			LerpRatio += 0.25f * Delta;

			if (LerpRatio < 1.0f)
			{
				float4 LerpColor = float4::Lerp(StartColor, EndColor, LerpRatio);
				EnemyRenderer->SetBlurColor(LerpColor, 3.0f - 3.0f * LerpRatio);
			}
			else
			{
				LerpRatio = 1.0f;
				EnemyRenderer->SetBlurColor(EndColor, 3.0f - 3.0f * LerpRatio);
			}
		},
		[this]
		{

		}
	);

	SetFSM(Boss_OldCrowState::DEATHWHILEUPRIGHT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("DeathInUpright");

			GameEngineSound::Play("OldCrow_Death.mp3");
		},
		[this](float Delta)
		{
			LerpRatio += 0.25f * Delta;
			
			if (LerpRatio < 1.0f)
			{
				float4 LerpColor = float4::Lerp(StartColor, EndColor, LerpRatio);
				EnemyRenderer->SetBlurColor(LerpColor, 3.0f - 3.0f * LerpRatio);
			}
			else
			{
				LerpRatio = 1.0f;
				EnemyRenderer->SetBlurColor(EndColor, 3.0f - 3.0f * LerpRatio);
			}
		},
		[this]
		{

		}
	);
}
