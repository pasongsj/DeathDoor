#include "PreCompileHeader.h"
#include "EnemyGhoulBig.h"
#include "EnemyAttackCapsule.h"

EnemyGhoulBig::EnemyGhoulBig()
{
}

EnemyGhoulBig::~EnemyGhoulBig()
{
}


//ArrowScale = floa
////ArrowRot = float4
//ArrowPhysXScale =

void EnemyGhoulBig::ShootArrow()
{
	// 본 위치 가져오기
	std::shared_ptr<GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
	BonePivot->GetTransform()->SetParent(GetTransform());
	BonePivot->GetTransform()->SetLocalPosition(EnemyRenderer->GetBoneData("Bow").Pos);
	float4 BonePivotPos = BonePivot->GetTransform()->GetWorldPosition();

	ShootDir = AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL);
	std::shared_ptr<EnemyAttackCapsule> Attack = GetLevel()->CreateActor<EnemyAttackCapsule>();
	Attack->SetRender(ArrowScale, ArrowRot);
	Attack->SetPhysXComp(ArrowPhysXScale, float4::DOWN * 100.0f, float4::LEFT);
	Attack->SetTrans(ShootDir, BonePivotPos);// 위치와 방향설정
	Attack->SetShoot(1000.0f);
	BonePivot->Death();
}

void EnemyGhoulBig::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();

	EnemyRenderer->SetFBXMesh("_E_GHOUL_RAPID_MESH.FBX", "ContentAniMeshDeffered");
	EnemyRenderer->CreateFBXAnimation("SHOOT_BOW", "_E_GHOUL_SHOOT_BOW_RAPID.fbx", { 1.f / 30.f,false });
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 36, std::bind(&EnemyGhoulBig::ShootArrow, this));
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 74, std::bind(&EnemyGhoulBig::ShootArrow, this));
	EnemyRenderer->SetAnimationStartFunc("SHOOT_BOW", 112, std::bind(&EnemyGhoulBig::ShootArrow, this));

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
			AggroMove(Delta);
			if (true == InRangePlayer(900.0f))
			{
				SetNextState(EnemyGhoulBigState::IDLE);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyGhoulBigState::SHOOT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SHOOT_BOW");
		},
		[this](float Delta)
		{
			AggroDir(m_pCapsuleComp, DEFAULT_DIR_GHOUL);
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

	SetFSM(EnemyGhoulBigState::HIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("HIT_BOW");
			AggroDir(m_pCapsuleComp);
		},
		[this](float Delta)
		{
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