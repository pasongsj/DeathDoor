#include "PreCompileHeader.h"
#include "EnemyJumper.h"
#include "EnemyAttackBox.h"

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

	EnemyRenderer->CreateFBXAnimation("BOOMER_CATCH", "JUMPER_BOOMER_CATCH.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("BOOMER_CATCH", 0, [this]
		{
			SetBoomerangState(BoomerangState::RIGHT);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_CATCH", 28, [this]
		{
			SetBoomerangState(BoomerangState::HEAD);
		});

	EnemyRenderer->CreateFBXAnimation("BOOMER_PREP_WAIT", "JUMPER_BOOMER_PREP_WAIT.fbx", { 1.0f / 30,false });

	EnemyRenderer->CreateFBXAnimation("BOOMER_THROW", "JUMPER_BOOMER_THROW.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 0, [this]
		{
			SetBoomerangState(BoomerangState::HEAD);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 22, [this]
		{
			SetBoomerangState(BoomerangState::LEFT);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 53, [this]
		{
			SetBoomerangState(BoomerangState::AIR);
		});

	EnemyRenderer->CreateFBXAnimation("SKIP_THROW", "JUMPER_SKIP_THROW.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 0, [this]
		{
			SetBoomerangState(BoomerangState::LEFT);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 22, [this]
		{
			SetBoomerangState(BoomerangState::AIR);
		});

	EnemyRenderer->CreateFBXAnimation("JUMP", "JUMPER_JUMP.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("JUMP", 12, [this]
		{
			JumpDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP", 50, [this]
		{
			JumpDir = float4::ZERO;
		});

	EnemyRenderer->CreateFBXAnimation("INTERRUPT", "JUMPER_INTERRUPT.fbx", { 1.0f / 30,false });
	EnemyRenderer->CreateFBXAnimation("DROWN", "JUMPER_DROWN.fbx", { 1.0f / 30,false });



	EnemyRenderer->ChangeAnimation("IDLE");
	EnemyRenderer->GetTransform()->SetLocalRotation(float4{ 90.0f,0.0f,0.0f });
}
void EnemyJumper::Start()
{
	EnemyBase::Start();
	//SetEnemyHP(m_iFullHP);
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_JUMPER);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_JUMPER);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	}
	SetFSMFUNC();
}

bool EnemyJumper::CheckBooemrang()
{
	if (CurBoomer == BoomerangState::AIR && true == CheckCollision(PhysXFilterGroup::JumperBoomer))
	{
		if (EnemyJumperState::HIT == GetCurState<EnemyJumperState>())
		{
			SetBoomerangState(BoomerangState::RIGHT);
			return true;
		}
		SetNextState(EnemyJumperState::CATCH);
	}
	return false;
}


void EnemyJumper::ThrowBoomer()
{
	float4 Dir = GetPlayerDir();
	//std::shared_ptr< EnemyAttackBox> Boomer = GetLevel()->CreateActor< EnemyAttackBox>();
}

void EnemyJumper::SetBoomerangState(BoomerangState _State)
{
	if (_State == EnemyJumper::BoomerangState::MAX)
	{
		MsgAssert("부메랑 위치 오류");
		return;
	}
	EnemyRenderer->SetRenderUnitControl(10, 0, false);
	EnemyRenderer->SetRenderUnitControl(14, 0, false);
	EnemyRenderer->SetRenderUnitControl(20, 0, false);
	switch (_State)
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
	{
		if (CurBoomer != BoomerangState::AIR)
		{
			ThrowBoomer();
		}
		break;
	}

	default:
		break;
	}
	CurBoomer = _State;

}



void EnemyJumper::JumpMove(float _DeltaTime)
{
	m_pCapsuleComp->SetMoveSpeed(JumpDir * JUMPER_MOVE_SPEED);
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
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT);
			}
			else if (true == CheckBooemrang())
			{
				return;
			}
			if (true == InRangePlayer(800.0f) || BoomerangState::AIR == CurBoomer)
			{
				SetNextState(EnemyJumperState::JUMP);
				return;
			}
			if (true == InRangePlayer(1200.0f) && BoomerangState::AIR != CurBoomer)
			{
				SetNextState(EnemyJumperState::THROW);
				return;
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
			CheckHit();

			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyJumperState::IDLE);
				return;
			}
		},
		[this]
		{
		}
	);
	// BOOMER_CATCH, BOOMER_PREP_WAIT
	SetFSM(EnemyJumperState::CATCH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("BOOMER_CATCH");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyJumperState::IDLE);
			}
		},
		[this]
		{
		}
	);
	// JUMP
	SetFSM(EnemyJumperState::JUMP,
		[this]
		{
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
			EnemyRenderer->ChangeAnimation("JUMP");
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyJumperState::IDLE);
			}
			JumpMove(Delta);
		},
		[this]
		{
		}
	);
	//INTERRUPT
	SetFSM(EnemyJumperState::HIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("INTERRUPT");
		},
		[this](float Delta)
		{
			CheckBooemrang();
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT,true);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState("IDLE");
			}
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




void EnemyJumper::Update(float _DeltaTime)
{
	if (nullptr == EnemyRenderer)
	{
		return;
	}
	FSMObjectBase::Update(_DeltaTime);
}

