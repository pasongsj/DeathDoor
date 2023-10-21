#include "PreCompileHeader.h"
#include "EnemyGrunt.h"
#include "EnemyAttackBox.h"
#include "Player.h"

EnemyGrunt::EnemyGrunt() 
{
}

EnemyGrunt::~EnemyGrunt() 
{
}


void EnemyGrunt::InitAniamtion()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_GRUNT_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "_E_GRUNT_IDLE.fbx", { 0.02f,true });
	EnemyRenderer->CreateFBXAnimation("DROWN", "_E_GRUNT_DROWN.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("WALK", "_E_GRUNT_WALK.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("RUN", "_E_GRUNT_RUN.fbx", { 0.02f,true });
	EnemyRenderer->CreateFBXAnimation("JUMP_START", "_E_GRUNT_JUMP_START.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("JUMP_MAIN", "_E_GRUNT_JUMP_MAIN.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("HIT", "_E_GRUNT_HIT.fbx", { 0.02f,false });

	EnemyRenderer->SetAnimationStartFunc("JUMP_MAIN", 20, [this]
		{
			m_pAttackBox = GetLevel()->CreateActor<EnemyAttackBox>();
			m_pAttackBox->SetScale(float4(50, 50, 50));
			m_pAttackBox->GetPhysXComponent()->SetDynamicPivot(float4(40, 0, 0));
			float4 f4MyPos = GetTransform()->GetWorldPosition();
			m_pAttackBox->SetTrans(m_f4ShootDir, f4MyPos);
		});

	EnemyRenderer->ChangeAnimation("IDLE");
}



void EnemyGrunt::Start()
{
	EnemyBase::Start();
	SetEnemyHP(4);
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_GRUNT);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_GRUNT);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	}
	SetFSMFUNC();
}

void EnemyGrunt::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);

}



void EnemyGrunt::AggroMove(float _DeltaTime)
{
	if (false == GetStateChecker())
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp) * GRUNT_MOVE_SPEED);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(AggroDir(m_pCapsuleComp) * GRUNT_MOVE_SPEED * 2.0f);

	}
}


void EnemyGrunt::SetFSMFUNC()
{
	InitFSM(EnemyGruntState::MAX);

	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});



	SetFSM(EnemyGruntState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGruntState::HIT);
				return;
			}
			if(true == InRangePlayer(1000.0f)) // 1500 이상으로 멀어진다면
			{
				SetNextState(EnemyGruntState::MOVE);
				return;
			}
			

		},
		[this]
		{
		}
	);

	SetFSM(EnemyGruntState::MOVE,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp);
			EnemyRenderer->ChangeAnimation("WALK");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGruntState::HIT);
				return;
			}
			if (false == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				EnemyRenderer->ChangeAnimation("RUN");
				SetStateCheckerOn();
				//StateChecker = true;
			}
			if (true == InRangePlayer(550.0f))
			{
				SetNextState(EnemyGruntState::JUMP_WAIT);
				return;
			}
			AggroMove(Delta);

		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(EnemyGruntState::JUMP_WAIT,
		[this]
		{
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				SetNextState(EnemyGruntState::HIT);
				return;
			}
			//StateDuration += Delta;


			if (GetStateDuration() > 0.5f)
			{
				if (false == InRangePlayer(550.0f))
				{
					SetNextState(EnemyGruntState::MOVE);
					return;
				}
				SetNextState(EnemyGruntState::JUMP);
				return;
			}
			m_f4ShootDir = AggroDir(m_pCapsuleComp);

		},
		[this]
		{
		}
	);
	SetFSM(EnemyGruntState::JUMP,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp);
		},
		[this](float Delta)
		{

		//	if (/*조건문 &&*/ false == GetStateChecker())
		//	{
		//		EnemyRenderer->ChangeAnimation("JUMP_MAIN");
		//		SetStateCheckerOn();
		//		return;
		//	}
		//	if (/*조건문 &&*/ true == GetStateChecker()&& nullptr == m_pAttackBox)
		//	{
		//		m_pAttackBox = GetLevel()->CreateActor<EnemyAttackBox>();
		//		m_pAttackBox->SetScale(float4(50, 50, 50));
		//		m_pAttackBox->GetPhysXComponent()->SetDynamicPivot(float4(40, 0, 0));
		//		float4 f4MyPos = GetTransform()->GetWorldPosition();
		//		m_pAttackBox->SetTrans(m_f4ShootDir, f4MyPos);
		//		return;
		//	}
		//	if (/*조건문 &&*/m_pAttackBox!=nullptr)
		//	{
		//		m_pAttackBox->Death();
		//		m_pAttackBox = nullptr;
		//		SetNextState(EnemyGruntState::IDLE);
		//		return;
		//	}
			//if (m_f4HeightPos.Size()<250.f&& false == GetStateChecker())
			//{
			//	EnemyRenderer->ChangeAnimation("JUMP_MAIN");
			//	if (true == EnemyRenderer->IsAnimationEnd())
			//	{
			//		m_pAttackBox->Death();
			//		SetNextState(EnemyGruntState::IDLE);
			//	}
			//	return;
			//}	
			//
			m_pCapsuleComp->SetMoveSpeed(m_f4ShootDir*500.f);
			if (true == EnemyRenderer->IsAnimationEnd()&& false == GetStateChecker())
			{
				EnemyRenderer->ChangeAnimation("JUMP_MAIN");
				SetStateCheckerOn();
			}
			if (true == GetStateChecker() )
			{
				if (true == EnemyRenderer->IsAnimationEnd())
				{
			
				m_pAttackBox->Death();
				SetNextState(EnemyGruntState::IDLE);
				return;
				}
			}

		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(EnemyGruntState::HIT,
		[this]
		{
			m_f4ShootDir = AggroDir(m_pCapsuleComp);
			EnemyRenderer->ChangeAnimation("HIT");
		},
		[this](float Delta)
		{
			if (true == CheckHit())
			{
				EnemyRenderer->ChangeAnimation("HIT",true);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyGruntState::IDLE);
				return;
			}

		},
		[this]
		{
		}
	);

	SetFSM(EnemyGruntState::DEATH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("DROWN");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
