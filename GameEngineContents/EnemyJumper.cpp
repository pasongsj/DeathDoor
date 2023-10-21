#include "PreCompileHeader.h"
#include "EnemyJumper.h"

EnemyJumper::EnemyJumper()
{
}

EnemyJumper::~EnemyJumper()
{
}


void EnemyJumper::InitAniamtion()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("JUMPER_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "JUMPER_IDLE.fbx", { 1.0f / 30,true });
	EnemyRenderer->CreateFBXAnimation("IDLE_LOOK", "JUMPER_IDLE_LOOK.fbx", { 1.0f / 30,false });
	EnemyRenderer->CreateFBXAnimation("HOP", "JUMPER_HOP.fbx", { 1.0f / 30,false });

	EnemyRenderer->CreateFBXAnimation("BOOMER_CATCH", "JUMPER_BOOMER_CATCH.fbx", { 1.0f / 30,true });
	EnemyRenderer->CreateFBXAnimation("BOOMER_PREP_WAIT", "JUMPER_BOOMER_PREP_WAIT.fbx", { 1.0f / 30,true });

	EnemyRenderer->CreateFBXAnimation("BOOMER_THROW", "JUMPER_BOOMER_THROW.fbx", { 1.0f / 30,true });
	EnemyRenderer->CreateFBXAnimation("SKIP_THROW", "JUMPER_SKIP_THROW.fbx", { 1.0f / 30,true });

	EnemyRenderer->CreateFBXAnimation("JUMP", "JUMPER_JUMP.fbx", { 1.0f / 30,true });

	EnemyRenderer->CreateFBXAnimation("INTERRUPT", "JUMPER_INTERRUPT.fbx", { 1.0f / 30,true });
	EnemyRenderer->CreateFBXAnimation("DROWN", "JUMPER_DROWN.fbx", { 1.0f / 30,true });



	EnemyRenderer->ChangeAnimation("IDLE");
}

void EnemyJumper::SetBoomerangPos(BoomerangState _Pos)
{
	EnemyRenderer->SetRenderUnitControl(10, 0, false);
	EnemyRenderer->SetRenderUnitControl(14, 0, false);
	EnemyRenderer->SetRenderUnitControl(20, 0, false);
	CurBoomer = _Pos;
	switch (_Pos)
	{
	case EnemyJumper::BoomerangState::HEAD:
		EnemyRenderer->SetRenderUnitControl(10, 0, true);
		break;

	case EnemyJumper::BoomerangState::LEFT: // 던지는 손
		EnemyRenderer->SetRenderUnitControl(20, 0, true);
		break;

	case EnemyJumper::BoomerangState::RIGHT: // 받는손
		EnemyRenderer->SetRenderUnitControl(14, 0, true);
		break;

	case EnemyJumper::BoomerangState::AIR:
		break;

	default:
		break;
	}
}

void EnemyJumper::IdleUpdate(float _deltaTime)
{
	
}


void EnemyJumper::SetFSMFUNC()
{
	InitFSM(EnemyJumperState::MAX);

	SetChangeFSMCallBack([this]
		{
		});

	//// IDLE, IDLE_LOOK, HOP
	SetFSM(EnemyJumperState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (false == GetStateChecker() && GetStateDuration() > 2.0f)
			{
				SetStateCheckerOn();
				EnemyRenderer->ChangeAnimation("IDLE_LOOK");
			}
			else if (true == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				SetStateCheckerOff();
				EnemyRenderer->ChangeAnimation("IDLE");
			}

			if (true == InRangePlayer(1000.0f))
			{
				SetNextState(EnemyJumperState::THROW);
			}

		},
		[this]
		{
		}
	);
	// BOOMER_THROW, SKIP_THROW
	SetFSM(EnemyJumperState::THROW,
		[this]
		{
			if (CurBoomer == BoomerangState::HEAD)
			{
				EnemyRenderer->ChangeAnimation("BOOMER_THROW");
			}
			else if (CurBoomer == BoomerangState::LEFT || CurBoomer == BoomerangState::RIGHT)
			{
				EnemyRenderer->ChangeAnimation("JUMPER_SKIP_THROW");
			}
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
	// BOOMER_CATCH, BOOMER_PREP_WAIT
	SetFSM(EnemyJumperState::CATCH,
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
	// JUMP
	SetFSM(EnemyJumperState::JUMP,
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
	//INTERRUPT
	SetFSM(EnemyJumperState::HIT,
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
	// DROWN
	SetFSM(EnemyJumperState::DEATH,
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


void EnemyJumper::Start()
{
}


void EnemyJumper::Update(float _DeltaTime)
{
}

