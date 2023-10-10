#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"
#include "Boss_OldCrowChain.h"

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

			ChainsPivot->GetTransform()->SetLocalPosition({0, 100, 0});

			StateCalTime = 0.0f; //준비 시간
			StateCalTime2 = 0.0f; //사슬 생성시간
			CurrentChainSpeed = ChainSpeed;
		},
		[this](float Delta)
		{
			SetLerpDirection(Delta);

			StateCalTime += Delta;
			StateCalTime2 += Delta;

			ChainsPivot->GetTransform()->AddLocalPosition(float4::FORWARD * CurrentChainSpeed * Delta);
			
			if (StateCalTime2 > 0.015f && CurrentChainSpeed == ChainSpeed)
			{
				std::shared_ptr<Boss_OldCrowChain> Chain = GetChain();

				Chain->GetTransform()->SetWorldPosition(m_pCapsuleComp->GetTransform()->GetWorldPosition());
				Chain->GetTransform()->SetParent(ChainsPivot->GetTransform());

				UsingChainNumber[0].push_back(Chain->GetChainNumber());

				StateCalTime2 = 0.0f;
			}

			if (StateCalTime >= 1.0f)
			{
				CurrentChainSpeed -= CurrentChainSpeed * 100.0f * Delta;

				if (CurrentChainSpeed < 0.0f)
				{
					CurrentChainSpeed = 0.0f;
				}
			}

			if (StateCalTime >= 2.0f)
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

			m_pCapsuleComp->SetMoveSpeed(m_pCapsuleComp->GetTransform()->GetWorldForwardVector()* MegaDashSpeed);

			if (StateCalTime >= 2.0f)
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
			BossRender->ChangeAnimation("MegaDashPrep");
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
