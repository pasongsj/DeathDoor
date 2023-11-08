#include "PrecompileHeader.h"
#include "EnemyWave.h"

#include "Frog_Septre.h"

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
	SetNextState(WaveState::Second_Wave);
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


		},
		[this](float Delta)
		{


		},
		[this]
		{

		}
	);

	SetFSM(WaveState::Second_Wave,
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

	SetFSM(WaveState::Third_Wave,
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
