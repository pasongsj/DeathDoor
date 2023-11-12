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
			std::shared_ptr<EnemyGrunt> Enemy = GetLevel()->CreateActor<EnemyGrunt>();
			Enemy->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos);
			Enemy->CreateFadeEffect();

			std::shared_ptr<EnemyJumper> Enemy2 = GetLevel()->CreateActor<EnemyJumper>();
			Enemy2->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos2);
			Enemy2->CreateFadeEffect();

			std::shared_ptr<EnemyGhoul> Enemy3 = GetLevel()->CreateActor<EnemyGhoul>();
			Enemy3->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos3);
			Enemy3->CreateFadeEffect();

			m_vEnemys.resize(3);
			m_vEnemys[0].m_pEnemy = Enemy;
			m_vEnemys[1].m_pEnemy = Enemy2;
			m_vEnemys[2].m_pEnemy = Enemy3;
		},
		[this](float Delta)
		{
			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys.size(); i++)
			{
				if (m_vEnemys[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys[i].m_bIsDeath = true;
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
			std::shared_ptr<EnemyMage> Enemy = GetLevel()->CreateActor<EnemyMage>();
			Enemy->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos);

			std::shared_ptr<EnemyGrunt> Enemy2 = GetLevel()->CreateActor<EnemyGrunt>();
			Enemy2->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos2);

			std::shared_ptr<EnemyGhoul> Enemy3 = GetLevel()->CreateActor<EnemyGhoul>();
			Enemy3->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos3);

			m_vEnemys.clear();
			m_vEnemys.resize(3);
			m_vEnemys[0].m_pEnemy = Enemy;
			m_vEnemys[1].m_pEnemy = Enemy2;
			m_vEnemys[2].m_pEnemy = Enemy3;
		},
		[this](float Delta)
		{
			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys.size(); i++)
			{
				if (m_vEnemys[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys[i].m_bIsDeath = true;
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
			std::shared_ptr<EnemyGhoulBig> Enemy = GetLevel()->CreateActor<EnemyGhoulBig>();
			Enemy->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos);

			std::shared_ptr<EnemyGrunt> Enemy2 = GetLevel()->CreateActor<EnemyGrunt>();
			Enemy2->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos2);

			std::shared_ptr<EnemyBrute> Enemy3 = GetLevel()->CreateActor<EnemyBrute>();
			Enemy3->GetPhysXComponent()->SetWorldPosWithParent(m_f4EnemyPos3);

			m_vEnemys.clear();
			m_vEnemys.resize(3);
			m_vEnemys[0].m_pEnemy = Enemy;
			m_vEnemys[1].m_pEnemy = Enemy2;
			m_vEnemys[2].m_pEnemy = Enemy3;
		},
		[this](float Delta)
		{
			int CheckCount = 0;
			for (size_t i = 0; i < m_vEnemys.size(); i++)
			{
				if (m_vEnemys[i].m_bIsDeath == true)
				{
					++CheckCount;
					continue;
				}

				// 구조체가 false 면 
				if (m_vEnemys[i].m_bIsDeath == false)
				{
					bool Check = m_vEnemys[i].m_pEnemy->DeathCheck();
					if (Check == true)
					{
						++CheckCount;
						m_vEnemys[i].m_bIsDeath = true;
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
