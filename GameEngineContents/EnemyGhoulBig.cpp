#include "PreCompileHeader.h"
#include "EnemyGhoulBig.h"
#include "EnemyAttackCapsule.h"

#include "Player.h"
#include "Map_NaviMesh.h"

EnemyGhoulBig::EnemyGhoulBig()
{
}

EnemyGhoulBig::~EnemyGhoulBig()
{
}




void EnemyGhoulBig::CreateArrow()
{
	ArrowActor = GetLevel()->CreateActor<EnemyAttackCapsule>();
	ArrowActor->SetRender(ArrowScale, ArrowRot);
	ArrowActor->SetPhysXComp(ArrowPhysXScale, float4::DOWN * 100.0f, float4::LEFT);

	BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("Bow").Pos);
	float4 BonePivotPos = BonePivot->GetTransform()->GetWorldPosition();

	ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL);
	if (nullptr != ArrowActor)
	{
		ArrowActor->SetTrans(ShootDir, BonePivotPos);// 위치와 방향설정
	}
}

void EnemyGhoulBig::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();

	EnemyRenderer->SetFBXMesh("_E_GHOUL_RAPID_MESH.FBX", "ContentAniMeshDeffered","GoolTexture.png", "GoolTextureBig.png");
	EnemyRenderer->CreateFBXAnimation("SHOOT_BOW", "_E_GHOUL_SHOOT_BOW_RAPID.fbx", { 1.f / 30.f,false });
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 20, [this]
		{
			GameEngineSound::Play("Ghoul_ArrowReady.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 30, [this]
		{
			GameEngineSound::Play("Ghoul_ReadySFX.mp3");
		});
	
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 37, std::bind(&EnemyGhoulBig::CreateArrow, this));
	
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 58, [this]
		{
			GameEngineSound::Play("Ghoul_ArrowReady.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 68, [this]
		{
			GameEngineSound::Play("Ghoul_ReadySFX.mp3");
		});
	
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 75, std::bind(&EnemyGhoulBig::CreateArrow, this));
		
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 96, [this]
		{
			GameEngineSound::Play("Ghoul_ArrowReady.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 95, [this]
		{
			GameEngineSound::Play("Ghoul_ReadySFX.mp3");
		});
	
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 36, [this]
		{
			if (nullptr != ArrowActor)
			{
				ArrowActor->SetShoot(1000.0f);
				GameEngineSound::Play("Ghoul_FireArrow.mp3");
			}
			ArrowActor = nullptr;
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 74, [this]
		{
			if (nullptr != ArrowActor)
			{
				ArrowActor->SetShoot(1000.0f);
				GameEngineSound::Play("Ghoul_FireArrow.mp3");
			}
			ArrowActor = nullptr;
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 102, [this]
		{
			if (nullptr != ArrowActor)
			{
				ArrowActor->SetShoot(1000.0f);
				GameEngineSound::Play("Ghoul_FireArrow.mp3");
			}
			ArrowActor = nullptr;
		});

	EnemyRenderer->CreateFBXAnimation("IDLE_BOW", "_E_GHOUL_IDLE_BOW.fbx", { 1.f / 30.f,true });

	EnemyRenderer->CreateFBXAnimation("RUN_BOW", "_E_GHOUL_RUN_BOW.fbx", { 1.f / 30.f,true });
	EnemyRenderer->CreateFBXAnimation("WALK", "_E_GHOUL_WALK.fbx", { 1.f / 30.f,false });


	EnemyRenderer->CreateFBXAnimation("HIT_BOW", "_E_GHOUL_HIT_BOW.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("DROWN", "_E_GHOUL_DROWN.fbx", { 1.f / 30.f,false });

	EnemyRenderer->ChangeAnimation("IDLE_BOW");
}


void EnemyGhoulBig::Start()
{
	EnemyBase::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_GHOUL_RAPID);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_GHOUL_RAPID);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);

	}
	BonePivot = CreateComponent<GameEngineComponent>();
	SetEnemyHP(GhoulFullHP);
}


void EnemyGhoulBig::Update(float _DeltaTime)
{
	if (nullptr == EnemyRenderer)
	{
		return;
	}
	if (DeathCheck() == true)
	{
		SetNextState(EnemyGhoulBigState::DEATH);
	}

	EnemyBase::Update(_DeltaTime);
	FSMObjectBase::Update(_DeltaTime);
}


void EnemyGhoulBig::AggroMove(float _DeltaTime)
{
	if (false == GetStateChecker())
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL) * GHOUL_MOVE_SPEED);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL) * GHOUL_MOVE_SPEED * 3.0f);
	}
}

void EnemyGhoulBig::SetFSMFUNC()
{
	InitFSM(EnemyGhoulBigState::MAX);

	SetChangeFSMCallBack([this]
		{
		});



	SetFSM(EnemyGhoulBigState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE_BOW");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGhoulBigState::HIT);
				return;
			}
			if (true == InRangePlayer(1000.0f))
			{
				AggroDir(m_pCapsuleComp);
				if (GetStateDuration() > Idle_WaitTime)
				{
					SetNextState(EnemyGhoulBigState::SHOOT);
				}
				return;
			}
			if (true == InRangePlayer(2000.0f))
			{
				SetNextState(EnemyGhoulBigState::MOVE);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyGhoulBigState::MOVE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("WALK");
			AggroDir(m_pCapsuleComp);
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGhoulBigState::HIT);
				return;
			}
			if (false == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				EnemyRenderer->ChangeAnimation("RUN_BOW");
				SetStateCheckerOn();
			}
			float4 f4Dir = GetPlayerDir();
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
					}
					else
					{
						SetNextState(EnemyGhoulBigState::IDLE);
						return;
					}
				}
				else if (false == m_pCapsuleComp->TriRayCast(f4MyPos, f4Dir, f4Point, PlayerDistance, Dummy)
					&& true == InRangePlayer(900.f))
				{
					SetNextState(EnemyGhoulBigState::SHOOT);
					return;
				}
			}

			NaviMove(f4Dir, GHOUL_MOVE_SPEED, DEFAULT_DIR_GHOUL);
		},
		[this]
		{
		}
	);

	SetFSM(EnemyGhoulBigState::SHOOT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SHOOT_BOW");
			CreateArrow();
		},
		[this](float Delta)
		{
			BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("Bow").Pos);
			float4 BonePivotPos = BonePivot->GetTransform()->GetWorldPosition();

			ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL);
			if (nullptr != ArrowActor)
			{
				ArrowActor->SetTrans(ShootDir, BonePivotPos);// 위치와 방향설정
			}
			if (true == CheckHit())
			{
				SetNextState(EnemyGhoulBigState::HIT);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyGhoulBigState::IDLE);
				return;
			}
		},
		[this]
		{
			if (nullptr != ArrowActor)
			{
				ArrowActor->Death();
				ArrowActor = nullptr;
			}
		}
	);

	SetFSM(EnemyGhoulBigState::HIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("HIT_BOW");
			AggroDir(m_pCapsuleComp);

			GameEngineSound::Play("Ghoul_GetDamage.mp3");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGhoulBigState::HIT);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyGhoulBigState::IDLE);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyGhoulBigState::DEATH,
		[this]
		{
			GameEngineSound::Play("Ghoul_Death.mp3");

			EnemyRenderer->ChangeAnimation("DROWN");
		},
		[this](float Delta)
		{
			float4 f4Result = float4::LerpClamp(float4(0.f, 0.f, 0.f), float4(-90.f, 0.f, 0.f), GetStateDuration());
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