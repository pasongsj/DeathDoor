#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"
#include "Boss_OldCrowChain.h"
#include "Player.h"
#include "Boss_OldCrowCrowHead.h"

#include <GameEngineBase/GameEngineRandom.h>

void Boss_OldCrow::SetFSMFUNC()
{
	//enum class Boss_OldCrowState //스테이트 별
	//{
	//	EMPTY,

	//	IDLE,

	//	//대쉬
	//	STARTDASH,
	//	DASH,
	//	TURN,

	//	//사슬
	//	MEGADASHPREP,
	//	MEGADASH,

	//	//연속 사슬
	//	MEGADASH2PREP,
	//	MEGADASH2,

	//	//점프
	//	JUMP,
	//	SLAM,
	//	SLAMIMPACT,

	//	//Egg
	//	EGG,

	//	//SmallCrow
	//	SCREAM,
	//	SCREAMMINI,

	//	//Death
	//	DEATHWHILERUNNING,

	//	DEATHWHILEUPRIGHT,
	//};

	SetFSM(Boss_OldCrowState::EMPTY,
		[this]
		{
			
		},
		[this](float Delta)
		{

		},
		[this]
		{
		}
	);


	SetFSM(Boss_OldCrowState::IDLE,
		[this]
		{
			if (nullptr == BossRender)
			{
				BossRender->ChangeAnimation("Idle");

			}
		},
		[this](float Delta)
		{
			if (true)
			{
				//std::shared_ptr<Boss_OldCrowCrowHead> test1 = GetLevel()->CreateActor<Boss_OldCrowCrowHead>();
				//test1->SetCrowHead(float4{ 0, 100, 0 }, float4{ 0, 0, 0 });

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
			BossRender->ChangeAnimation("DashStart");
		},
		[this](float Delta)
		{
			SetLerpDirection(Delta);

			if (BossRender->IsAnimationEnd())
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
			BossRender->ChangeAnimation("Dash");
			//m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * BOSS_OLDCROW_DASHSPEED);

			CurrentSpeed = BOSS_OLDCROW_DASHSPEED;
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(GetTransform()->GetWorldForwardVector() * CurrentSpeed);

			SetLerpDirection(Delta);
		},
		[this]
		{

		}
	);

	SetFSM(Boss_OldCrowState::TURN,
		[this]
		{
			BossRender->ChangeAnimation("TurnLeft");
			IsTurn = false;
		},
		[this](float Delta)
		{
			if (IsTurn)
			{
				SetLerpDirection(Delta * 10.0f);
			}

			if (BossRender->IsAnimationEnd())
			{
				SetNextPatternState();
			}
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASHPREP,
		[this]
		{
			BossRender->ChangeAnimation("MegaDashPrep");

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
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASHPREPRANDOMPOS,
		[this]
		{
			BossRender->ChangeAnimation("MegaDashPrep");

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
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH,
		[this]
		{
			BossRender->ChangeAnimation("MegaDash");

			ChainsPivots[0]->GetTransform()->SetParent(GetTransform());

			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

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

		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH2PREP,
		[this]
		{
			MegaDash2PatternTransformPivot->GetTransform()->SetWorldPosition(Player::MainPlayer->GetTransform()->GetWorldPosition());

			SettingChainPatternPivot();

			BossRender->ChangeAnimation("MegaDashPrep");
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

		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH2,
		[this]
		{
			BossRender->ChangeAnimation("MegaDash");

			MegaDash2PatternCount = 0;

			ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetParent(GetTransform());

			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

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

					ChainsPivots[MegaDash2PatternCount]->GetTransform()->SetParent(GetTransform());
				}
			}
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);

		}
	);

	SetFSM(Boss_OldCrowState::JUMP,
		[this]
		{
			BossRender->ChangeAnimation("Jump");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 EnemyPos = GetTransform()->GetWorldPosition();

			float4 Position = float4::LerpClamp(EnemyPos, PlayerPos, 0.5f); //목표 지점

			TargetPos = Position;
			TargetPos.y += 1250.0f;

			JumpDir = TargetPos - EnemyPos;
			JumpDir.Normalize();

			m_pCapsuleComp->TurnOffGravity();

			StateCalTime = 0.0f;

			SetDirection();
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			SetLerpDirection(Delta);

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 BossPos = GetTransform()->GetWorldPosition();

			float Value = BossPos.XYZDistance(TargetPos);
			//float Value2= Boss

			if (Value >= 30.0f)
			{
				m_pCapsuleComp->SetMoveSpeed(JumpDir * BOSS_OLDCROW_JUMPFORCE);
			}

			if (Value <= 30.0f && StateCalTime > 1.0f)
			{
				SetNextState(Boss_OldCrowState::SLAM);
				return;
			}
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
			SetDirection();
		}
	);

	SetFSM(Boss_OldCrowState::SLAM,
		[this]
		{
			BossRender->ChangeAnimation("Slam");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 BossPos = GetTransform()->GetWorldPosition();

			SlamDir = PlayerPos - BossPos;
			SlamDir.Normalize();
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(SlamDir * BOSS_OLDCROW_SLAMFORCE);

			//SetLerpDirection(Delta);

			float4 CollPoint = float4::ZERO;
			if (true == m_pCapsuleComp->RayCast(GetTransform()->GetWorldPosition(), float4::DOWN, CollPoint, 2000.0f))
			{
				if (CollPoint.y + 100.0f > GetTransform()->GetWorldPosition().y)// 땅에 도달하였는지 체크
				{
					SetNextState(Boss_OldCrowState::SLAMIMPACT);
					return;
				}
			}
		},
		[this]
		{
			m_pCapsuleComp->TurnOnGravity();
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(Boss_OldCrowState::SLAMIMPACT,
		[this]
		{
			BossRender->ChangeAnimation("SlamImpact");

		},
		[this](float Delta)
		{
			if (BossRender->IsAnimationEnd())
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
			BossRender->ChangeAnimation("Egg");
		},
		[this](float Delta)
		{
			if (BossRender->IsAnimationEnd())
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
			BossRender->ChangeAnimation("ScreamMini");

			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			if (BossRender->IsAnimationEnd())
			{
				SetNextPatternState();
			}

			if (true)
			{

			}
			else
			{

			}
		},
		[this]
		{
		}
	);

	SetNextState(Boss_OldCrowState::EMPTY);
}
