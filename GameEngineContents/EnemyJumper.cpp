#include "PreCompileHeader.h"
#include "EnemyJumper.h"
#include "Boomerang.h"
#include "EnemyAttackBox.h"
#include "Player.h"
#include "Map_NaviMesh.h"

EnemyJumper::EnemyJumper()
{
}

EnemyJumper::~EnemyJumper()
{
}


void EnemyJumper::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("JUMPER_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "JUMPER_IDLE.fbx", { 1.0f / 30,true });
	EnemyRenderer->CreateFBXAnimation("IDLE_LOOK", "JUMPER_IDLE_LOOK.fbx", { 1.0f / 30,false });
	EnemyRenderer->CreateFBXAnimation("HOP", "JUMPER_HOP.fbx", { 1.0f / 30,false });

	EnemyRenderer->CreateFBXAnimation("BOOMER_CATCH", "JUMPER_BOOMER_CATCH.fbx", { 1.0f / 30,false });
	EnemyRenderer->SetAnimationStartFunc("BOOMER_CATCH", 0, [this]
		{
			GameEngineSound::Play("Jumper_BoomerCatch.mp3");
			SetBoomerangState(BoomerangState::RIGHT);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_CATCH", 28, [this]
		{
			GameEngineSound::Play("Jumper_GripBoomer.mp3");
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
			GameEngineSound::Play("Jumper_GripBoomer.mp3");
			SetBoomerangState(BoomerangState::LEFT);
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 40, [this]
		{
			GameEngineSound::Play("Jumper_ThrowReady.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("BOOMER_THROW", 50, [this]
		{
			GameEngineSound::Play("Jumper_Throw_Scream.mp3");
			GameEngineSound::Play("Jumper_Throw.mp3");
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
	EnemyRenderer->SetAnimationStartFunc("SKIP_THROW", 13, [this]
		{
			GameEngineSound::Play("Jumper_ThrowReady.mp3");
			GameEngineSound::Play("Jumper_Throw_Scream.mp3");
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

			GameEngineSound::Play("Jumper_Jump.mp3");

		});
	EnemyRenderer->SetAnimationStartFunc("JUMP", 35, [this]
		{
			GameEngineSound::Play("Jumper_LandingScream.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP", 50, [this]
		{
			JumpDir = float4::ZERO;
			JumpAttack = GetLevel()->CreateActor<EnemyAttackBox>();
			JumpAttack->SetScale(float4{ 120.0f,10.0f,120.0f });
			JumpAttack->SetTrans(GetTransform()->GetWorldRotation(), GetTransform()->GetWorldPosition());

			GameEngineSound::Play("Jumper_Landing.mp3");
		});

	EnemyRenderer->CreateFBXAnimation("INTERRUPT", "JUMPER_INTERRUPT.fbx", { 1.0f / 30,false });
	EnemyRenderer->CreateFBXAnimation("DROWN", "JUMPER_DROWN.fbx", { 1.0f / 30,true });


	SetBoomerangState(BoomerangState::HEAD);
	EnemyRenderer->ChangeAnimation("IDLE");
	EnemyRenderer->GetTransform()->SetLocalRotation(float4{ 90.0f,0.0f,0.0f });
}
void EnemyJumper::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_JUMPER);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_JUMPER);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		if (nullptr != Player::MainPlayer)
		{
			m_pCapsuleComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
		}
	}
	SetEnemyHP(JumperFullHP);
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
		float4 Dir = AggroDir(m_pCapsuleComp);
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
				if (false == InRangePlayer(500.0f) && true == InRangePlayer(1200.0f))
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
			IdleDelayTime = 0.5f;
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
			m_pCapsuleComp->RigidSwitch(false);
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

			float4 f4Dir = GetPlayerDir();
			float JumperSpeed = 0.f;
			if (Map_NaviMesh::NaviMesh != nullptr)
			{

				float4 f4Point = float4::ZERONULL;
				float4 f4MyPos = m_pCapsuleComp->GetWorldPosition();
				float4 PlayerPos = Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
				float PlayerDistance = PlayerPos.XYZDistance(f4MyPos);

				UINT Dummy = -1;

				//사이에 벽이 있음
				if (true == m_pCapsuleComp->TriRayCast(f4MyPos, f4Dir, f4Point, PlayerDistance, Dummy))
				{

					float4 RoadDir = float4::ZERONULL;
					RoadDir = Map_NaviMesh::NaviMesh->GetPhysXComp()->FindRoadDir(f4MyPos, PlayerPos);
					if (RoadDir != float4::ZERONULL)
					{
						f4Dir = RoadDir;
						f4Dir.y = 0;
						float4 FrontPos = Map_NaviMesh::NaviMesh->GetPhysXComp()->FindRoadPos();
						FrontPos.y = 0;
						float4 MoveAmount = (FrontPos - f4MyPos);
						JumperSpeed = MoveAmount.Size() < 200.0f ? 0 : MoveAmount.Size();
						JumperSpeed = JumperSpeed / 1.5f;

						NaviMove(f4Dir, JumperSpeed, DEFAULT_DIR_JUMPER);
						return;
					}
					else
					{
						SetNextState(EnemyJumperState::IDLE);
						return;
					}
				}
			}		


			JumpMove(Delta);
		},
		[this]
		{
			JumpDir = float4::ZERO;
			throw_jump = true;
			IdleDelayTime = 0.5f;
			if (nullptr != JumpAttack)
			{
				JumpAttack->Death();
			}
			JumpAttack = nullptr;
			m_pCapsuleComp->RigidSwitch(true);

		}
	);
	//INTERRUPT
	SetFSM(EnemyJumperState::HIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("INTERRUPT");
			GameEngineSound::Play("Jumper_TakeDamage1.mp3");
		},
		[this](float Delta)
		{
			CheckBoomerang();
			if (true == CheckHit())
			{
				SetNextState(EnemyJumperState::HIT,true);
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
	// DROWN
	SetFSM(EnemyJumperState::DEATH,
		[this]
		{
			GameEngineSound::Play("Jumper_Death.mp3");

			EnemyRenderer->ChangeAnimation("DROWN");
			EnemyRenderer->GetTransform()->AddLocalPosition(float4(0, 1, 0));
			if (nullptr != Boomer)
			{
				Boomer->Death();
				Boomer = nullptr;
			}
		},
		[this](float Delta)
		{
			float4 f4Result = float4::LerpClamp(float4(90.f, 0.f, 0.f), float4(0.f, 0.f, 0.f), GetStateDuration());
			EnemyRenderer->GetTransform()->SetLocalRotation(f4Result);
			if (GetStateDuration() < 1.f)
			{
				EnemyRenderer->FadeOut(1.f, Delta);
			}
			else
			{
				Death();
			}
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
	if (DeathCheck() == true)
	{
		SetNextState(EnemyJumperState::DEATH);
	}

	EnemyBase::Update(_DeltaTime);
	FSMObjectBase::Update(_DeltaTime);
}

