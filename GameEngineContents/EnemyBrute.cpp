#include "PreCompileHeader.h"
#include "EnemyBrute.h"
#include "EnemyAttackSphere.h"
#include "EnemyAttackBox.h"
#include "PhysXControllerComponent.h"

EnemyBrute::EnemyBrute() 
{
}

EnemyBrute::~EnemyBrute() 
{
}


void EnemyBrute::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_BRUTE_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "_E_BRUTE_IDLE.fbx", { 1.f / 30.f,true });
	EnemyRenderer->CreateFBXAnimation("WALK", "_E_BRUTE_WALK.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("RUN", "_E_BRUTE_RUN.fbx", { 1.f / 30.f,true });
	EnemyRenderer->CreateFBXAnimation("SLAM", "_E_BRUTE_SLAM.fbx", { 1.f / 30.f,false });
	EnemyRenderer->CreateFBXAnimation("SWING", "_E_BRUTE_SWING.fbx", { 1.f/30.f,false });
	EnemyRenderer->CreateFBXAnimation("BREAK", "_E_BRUTE_BREAK.fbx", { 1.f/30.f,false });
	EnemyRenderer->CreateFBXAnimation("THROW", "_E_BRUTE_THROW.fbx", { 1.f/30.f,false });
	//EnemyRenderer->GetBoneData("test");

	//weapon weapon_end slampoint
	EnemyRenderer->SetAnimationStartFunc("SLAM", 10, [this]
		{
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
			std::shared_ptr<EnemyAttackSphere> Attack = GetLevel()->CreateActor<EnemyAttackSphere>();
			std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
			BonePivot->GetTransform()->SetParent(GetTransform());
			BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("hand_l").Pos);
			float4 TmpPos = BonePivot->GetTransform()->GetWorldPosition();
			Attack->SetTrans(m_f4ShootDir, TmpPos);
			BonePivot->Death();

		});
	EnemyRenderer->ChangeAnimation("IDLE");
}




void EnemyBrute::Start()
{
	EnemyBase::Start();
	SetEnemyHP(m_iFullHP);
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_BRUTE);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_BRUTE);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	}
}


void EnemyBrute::Update(float _DeltaTime)
{
	bool bDeath = DeathCheck();

	if (bDeath == true)
	{
		SetNextState(EnemyBruteState::DEATH);
	}

	FSMObjectBase::Update(_DeltaTime);

}



void EnemyBrute::AggroMove(float _DeltaTime)
{
	if (false == GetStateChecker())
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE) * GRUNT_MOVE_SPEED);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE) * GRUNT_MOVE_SPEED * 2.0f);

	}
}


void EnemyBrute::SetFSMFUNC()
{
	InitFSM(EnemyBruteState::MAX);

	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});



	SetFSM(EnemyBruteState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP == GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteState::IDLE;
				SetNextState(EnemyBruteState::BREAK,true);
				return;
			}
			if(true == InRangePlayer(2000.0f))
			{
				SetNextState(EnemyBruteState::MOVE);
				return;
			}


		},
		[this]
		{
		}
	);

	SetFSM(EnemyBruteState::MOVE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("WALK");
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
		},
		[this](float Delta)
		{
			//StateDuration += Delta;
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1&& m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteState::MOVE;
				SetNextState(EnemyBruteState::BREAK, true);
				return;
			}
			if (false == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				EnemyRenderer->ChangeAnimation("RUN");
				SetStateCheckerOn();
				//StateChecker = true;
			}
			if (true == InRangePlayer(300.0f))
			{
				SetNextState(EnemyBruteState::SWING);
				return;
			}
			if (GetStateDuration() > 5)
			{
				if (true == InRangePlayer(1500.0f))
				{
					SetNextState(EnemyBruteState::THROW);
					ResetStateDuration();
					//StateDuration = 0.0f;
					return;
				}
			}
			AggroMove(Delta);

		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(EnemyBruteState::SLAM,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

			EnemyRenderer->ChangeAnimation("SLAM",true);
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteState::SLAM;
				SetNextState(EnemyBruteState::BREAK, true);
				return;
			}

			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (nullptr!=m_pAttackBox)
				{
					m_pAttackBox->Death();
					m_pAttackBox = nullptr;
				}
				SetNextState(EnemyBruteState::IDLE);
			}

		},
		[this]
		{
		}
	);
	SetFSM(EnemyBruteState::SWING,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

			EnemyRenderer->ChangeAnimation("SWING",true);
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == bHit && (GetEnemyHP() % 3 == 1 && m_iFullHP != GetEnemyHP()))
			{
				m_ePrevState = EnemyBruteState::SWING;
				SetNextState(EnemyBruteState::BREAK, true);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (nullptr != m_pAttackBox)
				{
					m_pAttackBox->Death();
					m_pAttackBox = nullptr;
				}
				SetNextState(EnemyBruteState::SLAM);
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBruteState::THROW,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
			EnemyRenderer->ChangeAnimation("THROW");
		},
		[this](float Delta)
		{
			bool bHit = CheckHit();
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyBruteState::IDLE);
			}

		},
		[this]
		{
		}
	);
	SetFSM(EnemyBruteState::BREAK,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);
			EnemyRenderer->ChangeAnimation("BREAK",true);

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
			m_pCapsuleComp->SetWorldPosWithParent(m_pCapsuleComp->GetWorldPosition() +(-m_f4ShootDir * 100.f));
		}
	);

	SetFSM(EnemyBruteState::DEATH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
			m_f4ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_BRUTE);

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