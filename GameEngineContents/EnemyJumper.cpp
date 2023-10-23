#include "PreCompileHeader.h"
#include "EnemyJumper.h"
#include "Boomerang.h"

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
	EnemyRenderer->SetAnimationStartFunc("SKIP_THROW", 0, [this]
		{
			SetBoomerangState(BoomerangState::LEFT);
		});
	EnemyRenderer->SetAnimationStartFunc("SKIP_THROW", 22, [this]
		{
			SetBoomerangState(BoomerangState::AIR);
		});

	EnemyRenderer->CreateFBXAnimation("JUMP", "JUMPER_JUMP.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("JUMP", 12, [this]
		{
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
			float4 MoveAmount = (GetPlayerPosition() - GetTransform()->GetWorldPosition());
			MoveAmount.y = 0;
			MoveAmount = MoveAmount.Size() < 200.0f ? float4::ZERO : MoveAmount;
			JumpDir = (MoveAmount /1.5f);

		});
	EnemyRenderer->SetAnimationStartFunc("JUMP", 50, [this]
		{
			JumpDir = float4::ZERO;
		});

	EnemyRenderer->CreateFBXAnimation("INTERRUPT", "JUMPER_INTERRUPT.fbx", { 1.0f / 30,false });
	EnemyRenderer->CreateFBXAnimation("DROWN", "JUMPER_DROWN.fbx", { 1.0f / 30,false });


	SetBoomerangState(BoomerangState::HEAD);
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

bool EnemyJumper::CheckBoomerang()
{
	if (nullptr == Boomer)
	{
		return false;
	}

	if (CurBoomer == BoomerangState::AIR)
	{
		if (true == Boomer->Destroy)
		{
			if (EnemyJumperState::WAIT != GetCurState<EnemyJumperState>())
			{
				SetBoomerangState(BoomerangState::RIGHT);
			}
			else
			{
				SetNextState(EnemyJumperState::CATCH);
			}
			Boomer->Death();
			Boomer = nullptr;
			return true;
		}
	}
	return false;
}


void EnemyJumper::ThrowBoomer()
{
	if (Boomer == nullptr)
	{
		float4 Dir = GetPlayerDir();
		Boomer = GetLevel()->CreateActor< Boomerang>();
		float4 BonePivotPos = GetTransform()->GetWorldPosition() + float4{ 0.0f, 120.0f,0.0f };
		Boomer->SetTrans(Dir, BonePivotPos);
		Boomer->DestPostion = GetPlayerPosition() + Dir * 100.0f;
		Boomer->SetShoot(1200.0f);
		throw_jump = false;
	}
	
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
	m_pCapsuleComp->SetMoveSpeed(JumpDir /** JUMPER_MOVE_SPEED*/);
}


void EnemyJumper::AggroBoomer()
{
	if (Boomer == nullptr)
	{
		return;
	}
	float4 BoomerDir = (Boomer->GetTransform()->GetWorldPosition()) - (GetTransform()->GetWorldPosition());
	float4 Rot = float4::ZERO;
	Rot.y = float4::GetAngleVectorToVectorDeg360(BoomerDir, float4::FORWARD);
	Rot -= DEFAULT_DIR_JUMPER;
	m_pCapsuleComp->SetRotation(Rot);

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
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
		},
		[this](float Delta)
		{
			
			// idle animation
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

			// change next animation

			// 현재 부메랑이 허공에 있다면
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT);
				return;
			}
			IdleDelayTime -= Delta;
			if (BoomerangState::AIR == CurBoomer)
			{
				if (true == CheckBoomerang())// catch
				{
					return;
				}
				if (nullptr == Boomer)
				{
					MsgAssert("부메랑 실종");
					return;
				}

				if (false == throw_jump && BoomerangState::AIR == CurBoomer)
				{
					SetNextState(EnemyJumperState::JUMP);
					return;
				}
			}
			else
			{
				if (IdleDelayTime > 0.0f)
				{
					return;
				}
				if (false == InRangePlayer(800.0f) && true == InRangePlayer(1200.0f))
				{
					SetNextState(EnemyJumperState::THROW);
					return;
				}
				if (true == InRangePlayer(1500.0f))
				{
					SetNextState(EnemyJumperState::JUMP);
					return;
				}
			}
			

		},
		[this]
		{
		}
	);


	// DROWN
	SetFSM(EnemyJumperState::WAIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("BOOMER_PREP_WAIT");
		},
		[this](float Delta)
		{
			if (true == Boomer->BackTo && Boomer->DestPostion == float4::ZERONULL)
			{
				Boomer->SetDestPos(GetTransform()->GetWorldPosition());
			}
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT);
				return;
			}
			CheckBoomerang();
			AggroBoomer();

		},
		[this]
		{
			if (nullptr != Boomer)
			{
				Boomer->SetDestPos(GetTransform()->GetWorldPosition());
				Boomer->BackTo = true;
			}
		}
	);

	// BOOMER_THROW, SKIP_THROW
	SetFSM(EnemyJumperState::THROW,
		[this]
		{
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
			if (CurBoomer == BoomerangState::HEAD)
			{
				EnemyRenderer->ChangeAnimation("BOOMER_THROW");
			}
			else if (CurBoomer == BoomerangState::LEFT || CurBoomer == BoomerangState::RIGHT)
			{
				EnemyRenderer->ChangeAnimation("SKIP_THROW");
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
			IdleDelayTime = 1.0f;
		}
	);
	// BOOMER_CATCH, BOOMER_PREP_WAIT
	SetFSM(EnemyJumperState::CATCH,
		[this]
		{
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_JUMPER);
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
			if (true == CheckBoomerang())// 확인 필요함
			{
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (false == throw_jump)
				{
					SetNextState(EnemyJumperState::WAIT);

				}
				else
				{
					SetNextState(EnemyJumperState::IDLE);

				}
			}
			JumpMove(Delta);
		},
		[this]
		{
			JumpDir = float4::ZERO;
			throw_jump = true;
			IdleDelayTime = 1.0f;
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
			CheckBoomerang();
			//if (true == CheckHit())
			//{
			//	SetNextState(EnemyJumperState::HIT,true);
			//	return;
			//}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyJumperState::IDLE);
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

