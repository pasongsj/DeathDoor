#include "PrecompileHeader.h"
#include "EnemyWave.h"

#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"

#include "Frog_Septre.h"

#include "EnemyBrute.h"
#include "EnemyBruteGold.h"
#include "EnemyFirePlant.h"
#include "EnemyGhoul.h"
#include "EnemyGhoulBig.h"
#include "EnemyGrunt.h"
#include "EnemyJumper.h"
#include "EnemyMage.h"

EnemyWave::EnemyWave()
{
}

EnemyWave::~EnemyWave()
{
}

void EnemyWave::WaveStart()
{
	SetNextState(WaveState::First_Wave);
}

void EnemyWave::Start()
{
	InitComponent();
	SetFSMFUNC();

	{
		std::shared_ptr<EnemyGrunt> Enemy = GetLevel()->CreateActor<EnemyGrunt>();
		Enemy->GetPhysXComponent()->SetWorldPosWithParent(float4 { 0, 2000, 0 });

		std::shared_ptr<EnemyJumper> Enemy2 = GetLevel()->CreateActor<EnemyJumper>();
		Enemy2->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		std::shared_ptr<EnemyBruteGold> Enemy3 = GetLevel()->CreateActor<EnemyBruteGold>();
		Enemy3->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		m_vEnemys_1.resize(3);
		m_vEnemys_1[0].m_pEnemy = Enemy;
		m_vEnemys_1[1].m_pEnemy = Enemy2;
		m_vEnemys_1[2].m_pEnemy = Enemy3;

		// 지금 만들자마자 0.1초만에 페이드 아웃을 시키고
		// 에너미 업데이트에서 페이드인을 시키고 있다. 
		for (size_t i = 0; i < m_vEnemys_1.size(); i++)
		{
			m_vEnemys_1[i].m_pEnemy->CreateFadeEffect();
			m_vEnemys_1[i].m_pEnemy->Off();
		}
	}
	{
		std::shared_ptr<EnemyBrute> Enemy = GetLevel()->CreateActor<EnemyBrute>();
		Enemy->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		std::shared_ptr<EnemyGrunt> Enemy2 = GetLevel()->CreateActor<EnemyGrunt>();
		Enemy2->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });


		std::shared_ptr<EnemyJumper> Enemy3 = GetLevel()->CreateActor<EnemyJumper>();
		Enemy3->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		m_vEnemys_2.resize(3);
		m_vEnemys_2[0].m_pEnemy = Enemy;
		m_vEnemys_2[1].m_pEnemy = Enemy2;
		m_vEnemys_2[2].m_pEnemy = Enemy3;

		for (size_t i = 0; i < m_vEnemys_2.size(); i++)
		{
			m_vEnemys_2[i].m_pEnemy->CreateFadeEffect();
			m_vEnemys_2[i].m_pEnemy->Off();
		}
	}
	{
		std::shared_ptr<EnemyFirePlant> Enemy = GetLevel()->CreateActor<EnemyFirePlant>();
		Enemy->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		std::shared_ptr<EnemyGrunt> Enemy2 = GetLevel()->CreateActor<EnemyGrunt>();
		Enemy2->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		std::shared_ptr<EnemyBrute> Enemy3 = GetLevel()->CreateActor<EnemyBrute>();
		Enemy3->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 2000, 0 });

		m_vEnemys_3.resize(3);
		m_vEnemys_3[0].m_pEnemy = Enemy;
		m_vEnemys_3[1].m_pEnemy = Enemy2;
		m_vEnemys_3[2].m_pEnemy = Enemy3;

		for (size_t i = 0; i < m_vEnemys_3.size(); i++)
		{
			m_vEnemys_3[i].m_pEnemy->CreateFadeEffect();
			m_vEnemys_3[i].m_pEnemy->Off();
		}
	}
}

void EnemyWave::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}

void EnemyWave::InitComponent()
{
}

void EnemyWave::SetFSMFUNC()
{
	InitFSM(WaveState::MAX);
	
	SetFSM(WaveState::Stand_By,
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

	SetFSM(WaveState::First_Wave,
		[this]
		{
			for (size_t i = 0; i < m_vEnemys_1.size(); i++)
			{
				m_vEnemys_1[i].m_pEnemy->On();
				m_vEnemys_1[i].m_pEnemy->GetPhysXComponent()->SetWorldPosWithParent(m_vEnemysPos[i]);
			}
		},
		[this](float Delta)
		{
			for (size_t i = 0; i < m_vEnemys_1.size(); i++)
			{
				if (m_vEnemys_1[i].m_bIsDeath == false && m_vEnemys_1[i].m_pEnemy->IsFadeEffet() == true)
				{
					m_vEnemys_1[i].m_pEnemy->FadeInEffect(Delta);
				}
			}

			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys_1.size(); i++)
			{
				if (m_vEnemys_1[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys_1[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys_1[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys_1[i].m_bIsDeath = true;
					}
				}
			}

			if (CheckCount == 3)
			{
				SetNextState(WaveState::Second_Wave);
			}

		},
		[this]
		{

		}
	);

	SetFSM(WaveState::Second_Wave,
		[this]
		{
			for (size_t i = 0; i < m_vEnemys_2.size(); i++)
			{
				m_vEnemys_2[i].m_pEnemy->On();
				m_vEnemys_2[i].m_pEnemy->GetPhysXComponent()->SetWorldPosWithParent(m_vEnemysPos[i]);
			}
		},
		[this](float Delta)
		{
			for (size_t i = 0; i < m_vEnemys_2.size(); i++)
			{
				if (m_vEnemys_2[i].m_bIsDeath == false && m_vEnemys_2[i].m_pEnemy->IsFadeEffet() == true)
				{
					m_vEnemys_2[i].m_pEnemy->FadeInEffect(Delta);
				}
			}

			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys_2.size(); i++)
			{
				if (m_vEnemys_2[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys_2[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys_2[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys_2[i].m_bIsDeath = true;
					}
				}
			}

			if (CheckCount == 3)
			{
				SetNextState(WaveState::Third_Wave);
			}
		},
		[this]
		{

		}
	);

	SetFSM(WaveState::Third_Wave,
		[this]
		{
			for (size_t i = 0; i < m_vEnemys_3.size(); i++)
			{
				m_vEnemys_3[i].m_pEnemy->On();
				m_vEnemys_3[i].m_pEnemy->GetPhysXComponent()->SetWorldPosWithParent(m_vEnemysPos[i]);
			}
		},
		[this](float Delta)
		{
			for (size_t i = 0; i < m_vEnemys_3.size(); i++)
			{
				if (m_vEnemys_3[i].m_bIsDeath == false && m_vEnemys_3[i].m_pEnemy->IsFadeEffet() == true)
				{
					m_vEnemys_3[i].m_pEnemy->FadeInEffect(Delta);
				}
			}

			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys_3.size(); i++)
			{
				if (m_vEnemys_3[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys_3[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys_3[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys_3[i].m_bIsDeath = true;
					}
				}
			}

			if (CheckCount == 3)
			{
				SetNextState(WaveState::End);
			}
		},
		[this]
		{

		}
	);

	SetFSM(WaveState::End,
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

}
