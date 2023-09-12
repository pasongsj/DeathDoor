#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"

void Boss_OldCrow::StateMachineInit()
{
	//Idle
	{
		BossStateParameter IdleState;

		IdleState.Start = [this]()
			{
				EnemyRenderer->ChangeAnimation("Dash");
			};

		IdleState.Update = [this](float _DeltaTIme)
			{
				if (EnemyRenderer->IsAnimationEnd())
				{
					int a = 0;
				}
			};

		IdleState.End = [this]()
			{
				int a = 0;
			};

		StateMap[Boss_OldCrowState::IDLE] = IdleState;
	}

	ChangeState(StateMap[Boss_OldCrowState::IDLE]);
}

////Idle
//{
//	BossStateParameter IdleParameter;
//
//	IdleParameter.Start = [this]()
//		{
//
//		};
//
//	IdleParameter.Update = [this](float _DeltaTIme)
//		{
//
//		};
//
//	IdleParameter.End = [this]()
//		{
//
//		};
//}