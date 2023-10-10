#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"
#include "Boss_OldCrowChain.h"
#include "Player.h"

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
			BossRender->ChangeAnimation("Idle");
		},
		[this](float Delta)
		{
			if (true)
			{
				SetRandomPattern();
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
			m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * DashSpeed);
		},
		[this](float Delta)
		{
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
		}
	);

	SetFSM(Boss_OldCrowState::MEGADASHPREP,
		[this]
		{
			BossRender->ChangeAnimation("MegaDashPrep");

			ChainsPivots[0]->GetTransform()->SetParent(m_pCapsuleComp->GetTransform());
			ChainsPivots[0]->GetTransform()->SetLocalPosition({ 0, 0, 0 });

			StateCalTime = 0.0f; //사슬 멈추는 시간
			
			CurrentChainSpeed = ChainSpeed;
		},
		[this](float Delta)
		{
			//SetLerpDirection(Delta);

			StateCalTime += Delta;

			ChainsPivots[0]->GetTransform()->AddLocalPosition(float4::FORWARD * CurrentChainSpeed * Delta);

			float Value1 = ChainsPivots[0]->GetTransform()->GetLocalPosition().z;
			float Value2 = (UsingChainNumber[0].size()) * 3.2f;

			//fix : 거리 구하는 공식 오류 수정해야 함
			if (Value1 >= Value2)
			{
				std::shared_ptr<Boss_OldCrowChain> Chain = GetChain();

				Chain->GetTransform()->SetParent(ChainsPivots[0]->GetTransform());

				UsingChainNumber[0].push_back(Chain->GetChainNumber());

				Chain->GetTransform()->SetLocalPosition({0, 0, UsingChainNumber[0].size() * - 5.0f });
			}

			if (StateCalTime >= CreateChainTime)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime >= 1.75f)
			{
				SetNextState(Boss_OldCrowState::MEGADASH);
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

			//float RandomValue = 500.0f;
			//float4 PlayerPos = Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
			//float4 RandomPos = { PlayerPos.x + GameEngineRandom::MainRandom.RandomFloat(500, 1000), 0 ,  PlayerPos.z + GameEngineRandom::MainRandom.RandomFloat(500, 1000) };

			m_pCapsuleComp->SetWorldPosWithParent(GetRandomPos(2000.0f), float4::ZERO);
			
			SetDirection();

			StateCalTime = 0.0f; //사슬 멈추는 시간

			CurrentChainSpeed = ChainSpeed;

			ChainsPivots[0]->GetTransform()->SetParent(m_pCapsuleComp->GetTransform());
			ChainsPivots[0]->GetTransform()->SetLocalPosition({0, 0, 0});
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			ChainsPivots[0]->GetTransform()->AddLocalPosition(float4::FORWARD * CurrentChainSpeed * Delta);

			float Value1 = ChainsPivots[0]->GetTransform()->GetLocalPosition().z;
			float Value2 = (UsingChainNumber[0].size()) * 3.2f;

			//fix : 거리 구하는 공식 오류 수정해야 함
			if (Value1 >= Value2)
			{
				std::shared_ptr<Boss_OldCrowChain> Chain = GetChain();

				Chain->GetTransform()->SetParent(ChainsPivots[0]->GetTransform());

				float4 Pos = m_pCapsuleComp->GetTransform()->GetWorldPosition();

				UsingChainNumber[0].push_back(Chain->GetChainNumber());

				Chain->GetTransform()->SetLocalPosition({ 0, 0, UsingChainNumber[0].size() * - 5.0f });
			}

			if (StateCalTime >= CreateChainTime)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime >= 1.75f)
			{
				SetNextState(Boss_OldCrowState::MEGADASH);
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

			StateCalTime = 0.0f;
		},
		[this](float Delta)
		{
			StateCalTime += Delta;

			m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector() * MegaDashSpeed);

			if (StateCalTime >= 1.0f)
			{
				SetNextPatternState();
			}
		},
		[this]
		{
			for (int i = 0; i < UsingChainNumber[0].size(); ++i)
			{
				Chains[UsingChainNumber[0][i]]->SetDefault();
			}

			UsingChainNumber[0].clear();

			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);

		}
	);

	SetFSM(Boss_OldCrowState::MEGADASH2PREP,
		[this]
		{
			//SettingChainPatternParameter();

			BossRender->ChangeAnimation("MegaDashPrep");

			//m_pCapsuleComp->SetWorldPosWithParent(ChainPatternParameterVector[0].StartPos, ChainPatternParameterVector[0].Dir);

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

	SetFSM(Boss_OldCrowState::JUMP,
		[this]
		{
			BossRender->ChangeAnimation("Jump");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			float4 EnemyPos = GetTransform()->GetWorldPosition();

			float4 Position = float4::LerpClamp(EnemyPos, PlayerPos, 0.5f); //목표 지점

			TargetPos = Position;
			TargetPos.y += 50.0f;

			JumpForce = TargetPos - GetTransform()->GetWorldPosition();
			JumpForce.Normalize();
			m_pCapsuleComp->TurnOffGravity();

			//m_pCapsuleComp->TurnOffGravity();
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(JumpForce*100.f);

			SetLerpDirection(Delta);

			float test = TargetPos.XYZDistance(GetTransform()->GetWorldPosition());
			if (TargetPos.XYZDistance(GetTransform()->GetWorldPosition()) < 10.0f )
			{
				m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
				SetNextState(Boss_OldCrowState::SLAM);
			}
		},
		[this]
		{
		}
	);

	SetFSM(Boss_OldCrowState::SLAM,
		[this]
		{
			BossRender->ChangeAnimation("Slam");

			float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();

			TargetPos = PlayerPos;
		},
		[this](float Delta)
		{
			m_pCapsuleComp->SetMoveSpeed(TargetPos - GetTransform()->GetWorldPosition());

			SetLerpDirection(Delta);

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

	SetNextState(Boss_OldCrowState::EMPTY);
}
