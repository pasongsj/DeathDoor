#include "PreCompileHeader.h"
#include "EnemyGrunt.h"
#include "EnemyAttackBox.h"
#include "Player.h"
#include "Map_NaviMesh.h"

EnemyGrunt::EnemyGrunt() 
{
}

EnemyGrunt::~EnemyGrunt() 
{
}


void EnemyGrunt::InitAnimation()
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

	EnemyRenderer->SetAnimationStartFunc("JUMP_MAIN", 5, [this]
		{
			SetStateCheckerOn();
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_MAIN", 20, [this]
		{
			SetStateCheckerOff();
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_MAIN", 25, [this]
		{
			SetNextState(EnemyGruntState::IDLE);
		});

	EnemyRenderer->ChangeAnimation("IDLE");
}



void EnemyGrunt::Start()
{
	EnemyBase::Start();
	SetEnemyHP(GruntFullHP);
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_GRUNT);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_GRUNT);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		m_pCapsuleComp->CreateSubShape(SubShapeType::BOX, float4(60, 10, 100), float4(0,0,50));
	}
}

void EnemyGrunt::Update(float _DeltaTime)
{
	bool bDeath = DeathCheck();

	if (bDeath == true)
	{
		SetNextState(EnemyGruntState::DEATH);
	}

	EnemyBase::Update(_DeltaTime);
	FSMObjectBase::Update(_DeltaTime);
}



void EnemyGrunt::AggroMove(float _DeltaTime)
{	
	if (false == GetStateChecker())
	{
		m_pCapsuleComp->SetMoveSpeed(m_f4ShootDir * GRUNT_MOVE_SPEED);
	}
	else
	{
		m_pCapsuleComp->SetMoveSpeed(m_f4ShootDir * GRUNT_MOVE_SPEED * 2.0f);

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
			//m_f4ShootDir = AggroDir(m_pCapsuleComp);
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
			//if (true == InRangePlayer(800.0f))
			//{
			//	SetNextState(EnemyGruntState::JUMP_WAIT);
			//	return;
			//}
			
			if (false == InRangePlayer(10000.0f))
			{
				SetNextState(EnemyGruntState::IDLE);
				return;
			}

			float4 f4Point = float4::ZERONULL;
			float4 f4Dir = GetPlayerDir();
			float4 f4MyPos = m_pCapsuleComp->GetWorldPosition();
			float4 NextPos = m_pCapsuleComp->GetWorldPosition() + (f4Dir * GRUNT_MOVE_SPEED);
			float4 PlayerPos = Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
			float PlayerDistance = PlayerPos.XYZDistance(f4MyPos);
			float TargetDistance = NextPos.XYZDistance(f4MyPos);
			
			UINT Dummy = -1;

			if (((true == m_pCapsuleComp->RayCast(f4MyPos, f4Dir, f4Point, PlayerDistance|| true == m_pCapsuleComp->RayCast(f4MyPos, f4Dir, f4Point, TargetDistance))
					|| false == m_pCapsuleComp->TriRayCast(NextPos, float4::DOWN, f4Point, 1000.f, Dummy))))
			{

				float4 RoadDir = float4::ZERONULL;
				RoadDir = Map_NaviMesh::NaviMesh->GetPhysXComp()->FindRoadDir(f4MyPos, PlayerPos);
				if (RoadDir != float4::ZERONULL)
				{
					f4Dir = RoadDir;
				}
				else
				{
					SetNextState(EnemyGruntState::IDLE);
					return;
				}

			}
			else
			{
				int a = 0;
				//SetNextState(EnemyGruntState::JUMP_WAIT);
			}

			NaviMove(f4Dir, GRUNT_MOVE_SPEED);
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
				if (false == InRangePlayer(800.0f))
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
			EnemyRenderer->ChangeAnimation("JUMP_START");
			m_f4ShootDir = AggroDir(m_pCapsuleComp);
			m_pCapsuleComp->AttachShape();
			m_f4TargetPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			m_f4WaitPos = GetTransform()->GetWorldPosition();
			m_fDistance = m_f4TargetPos.XYZDistance(m_f4WaitPos); 
			m_fDistance += GRUNT_JUMP_SPEED;
		},
		[this](float Delta)
		{
			CheckHit();
			if (true == EnemyRenderer->IsAnimationEnd()&& false == GetStateChecker())
			{
				EnemyRenderer->ChangeAnimation("JUMP_MAIN");
				m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
			}
			if (true == GetStateChecker() )
			{
				m_pCapsuleComp->SetMoveSpeed(m_f4ShootDir * m_fDistance);
			}

		},
		[this]
		{
			m_pCapsuleComp->DetachShape();
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
