#include "PreCompileHeader.h"
#include "EnemyBruteGold.h"

#include "EnemyAttackBox.h"
#include "EnemyAttackSphere.h"
#include "Player.h"
#include "Map_NaviMesh.h"

EnemyBruteGold::EnemyBruteGold() 
{
}

EnemyBruteGold::~EnemyBruteGold() 
{
}


void EnemyBruteGold::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_BRUTE_GOLD_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE",  "_E_BRUTE_GOLD_IDLE.fbx", { 1.f / 30.f,true });
	EnemyRenderer->CreateFBXAnimation("WALK",  "_E_BRUTE_GOLD_WALK.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("RUN",   "_E_BRUTE_GOLD_RUN.fbx", { 1.f / 30.f,true });
	EnemyRenderer->CreateFBXAnimation("SLAM",  "_E_BRUTE_GOLD_SLAM.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("SWING", "_E_BRUTE_GOLD_SWING.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("BREAK", "_E_BRUTE_GOLD_BREAK.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("THROW", "_E_BRUTE_GOLD_THROW.fbx", { 1.f / 30.f,false });

	EnemyRenderer->SetAnimationStartFunc("SLAM", 10, [this]
		{
			GameEngineSound::Play("Brute_Attack2.mp3");

			m_pAttackBox = GetLevel()->CreateActor<EnemyAttackBox>();
			m_pAttackBox->SetScale(float4(200, 60, 70));
			m_pAttackBox->GetPhysXComponent()->SetDynamicPivot(float4(-200, 0, -70));
			std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
			BonePivot->GetTransform()->SetParent(GetTransform());
			BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("slampoint").Pos);
			float4 TmpPos = BonePivot->GetTransform()->GetWorldPosition();
			m_pAttackBox->SetTrans(m_f4ShootDir, TmpPos);
			BonePivot->Death();

		});
	EnemyRenderer->SetAnimationStartFunc("SWING", 23, [this]
		{
			GameEngineSound::Play("Brute_Attack2.mp3");

			m_pAttackBox = GetLevel()->CreateActor<EnemyAttackBox>();
			m_pAttackBox->SetScale(float4(200, 60, 70));
			m_pAttackBox->GetPhysXComponent()->SetDynamicPivot(float4(-70, -20, -270));
			std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
			BonePivot->GetTransform()->SetParent(GetTransform());
			BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("slampoint").Pos);
			float4 TmpPos = BonePivot->GetTransform()->GetWorldPosition();
			m_pAttackBox->SetTrans(m_f4ShootDir, TmpPos);
			BonePivot->Death();

		});

	EnemyRenderer->SetAnimationStartFunc("THROW", 15, [this]
		{
			GameEngineSound::Play("Brute_BombThrow.mp3");

			std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
			BonePivot->GetTransform()->SetParent(GetTransform());
			BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("hand_l").Pos);
			float4 TmpPos = BonePivot->GetTransform()->GetWorldPosition();

			std::shared_ptr<EnemyAttackSphere> Attack = GetLevel()->CreateActor<EnemyAttackSphere>();
			Attack->SetRender(FIREPLANT_ATT_RENDER_SCALE * 2.f);
			Attack->SetPhysXComp(FIREPLANT_ATT_PHYSX_SCALE * 2.f);
			Attack->SetTrans(m_f4ShootDir, TmpPos);
			Attack->SetEndSound("Brute_BombBoom.mp3");

			std::shared_ptr<ContentFBXRenderer> Rend = Attack->GetRenderer();
			Rend->SetGlowToUnit(0, 0);
			Rend->SetUnitColor(0, 0, float4::RED, 5);
			Attack->SetDustColor({ 255.0f / 255.0f, 198.0f / 255.0f , 198.0f / 255.0f });
			Attack->SetShoot(1000.0f);

			BonePivot->Death();

		});

	//Sound
	EnemyRenderer->SetAnimationStartFunc("WALK", 22, [this]
		{
			GameEngineSound::Play("Brute_Walk.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("WALK", 38, [this]
		{
			GameEngineSound::Play("Brute_Walk.mp3");
		});

	EnemyRenderer->SetAnimationStartFunc("RUN", 10, [this]
		{
			GameEngineSound::Play("Brute_Walk.mp3");
		});
	EnemyRenderer->SetAnimationStartFunc("RUN", 19, [this]
		{
			GameEngineSound::Play("Brute_Walk.mp3");
		});

	EnemyRenderer->ChangeAnimation("IDLE");
}



void EnemyBruteGold::Start()
{
	EnemyBase::Start();
	SetEnemyHP(m_iFullHP);

	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_BRUTEGOLD);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_BRUTEGOLD);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	}
}


void EnemyBruteGold::Update(float _DeltaTime)
{
	bool bDeath = DeathCheck();

	if (bDeath == true)
	{
		SetNextState(EnemyBruteGoldState::DEATH);
	}

	EnemyBase::Update(_DeltaTime);
	FSMObjectBase::Update(_DeltaTime);
}



void EnemyBruteGold::AggroMove(float _DeltaTime)
{
	if (false == GetStateChecker())
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTEGOLD) * GRUNT_MOVE_SPEED);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTEGOLD) * GRUNT_MOVE_SPEED * 2.0f);

	}
}


void EnemyBruteGold::SetFSMFUNC()
{
	InitFSM(EnemyBruteGoldState::MAX);

	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});



	SetFSM(EnemyBruteGoldState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{

			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP == GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteGoldState::IDLE;
				SetNextState(EnemyBruteGoldState::BREAK, true);
				return;
			}
			if (true == InRangePlayer(2000.0f))
			{
				SetNextState(EnemyBruteGoldState::MOVE);
				return;
			}

		},
		[this]
		{
		}
	);

	SetFSM(EnemyBruteGoldState::MOVE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("WALK");
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
		},
		[this](float Delta)
		{
			//StateDuration += Delta;
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteGoldState::MOVE;
				SetNextState(EnemyBruteGoldState::BREAK, true);
				return;
			}
			if (false == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				EnemyRenderer->ChangeAnimation("RUN");
				SetStateCheckerOn();
				//StateChecker = true;
			}
			if (GetStateDuration() > 5)
			{
				if (true == InRangePlayer(1500.0f))
				{
					SetNextState(EnemyBruteGoldState::THROW);
					ResetStateDuration();
					//StateDuration = 0.0f;
					return;
				}
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
						SetNextState(EnemyBruteGoldState::IDLE);
						return;
					}
				}
				else if (false == m_pCapsuleComp->TriRayCast(f4MyPos, f4Dir, f4Point, PlayerDistance, Dummy)
					&& true == InRangePlayer(300.0f))
				{
					SetNextState(EnemyBruteGoldState::SWING);
					return;
				}
			}

			NaviMove(f4Dir, GRUNT_MOVE_SPEED, DEFAULT_DIR_BRUTEGOLD);
		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(EnemyBruteGoldState::SLAM,
		[this]
		{
			GameEngineSound::Play("Brute_AttackReady.mp3");

			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

			EnemyRenderer->ChangeAnimation("SLAM", true);
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteGoldState::SLAM;
				SetNextState(EnemyBruteGoldState::BREAK, true);
				return;
			}

			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (nullptr != m_pAttackBox)
				{
					m_pAttackBox->Death();
					m_pAttackBox = nullptr;
				}
				SetNextState(EnemyBruteGoldState::IDLE);
			}

		},
		[this]
		{
		}
	);
	SetFSM(EnemyBruteGoldState::SWING,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

			GameEngineSound::Play("Brute_AttackReady.mp3");

			EnemyRenderer->ChangeAnimation("SWING", true);
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteGoldState::SWING;
				SetNextState(EnemyBruteGoldState::BREAK, true);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (nullptr != m_pAttackBox)
				{
					m_pAttackBox->Death();
					m_pAttackBox = nullptr;
				}
				SetNextState(EnemyBruteGoldState::SLAM);
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBruteGoldState::THROW,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
			EnemyRenderer->ChangeAnimation("THROW");

			GameEngineSound::Play("Brute_AttackReady.mp3");
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyBruteGoldState::IDLE);
			}

		},
		[this]
		{
		}
	);

	SetFSM(EnemyBruteGoldState::BREAK,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
			EnemyRenderer->ChangeAnimation("BREAK", true);

			GameEngineSound::Play("Brute_GetDamage.mp3");
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(m_ePrevState);
				return;
			}
		},
		[this]
		{
			m_pCapsuleComp->SetWorldPosWithParent(m_pCapsuleComp->GetWorldPosition() + (-m_f4ShootDir * 100.f));
		}
	);

	SetFSM(EnemyBruteGoldState::DEATH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

			GameEngineSound::Play("Brute_Death.mp3");
		},
		[this](float Delta)
		{
			//로테이션 러프시켜서 렌더러 돌리고 아이들상태로 죽여버리기
			//float4 f4CurRot = EnemyRenderer->GetTransform

			float4 f4Result = float4::LerpClamp(float4(0.f, 0.f, 0.f), float4(0.f, 0.f, 90.f), GetStateDuration());
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