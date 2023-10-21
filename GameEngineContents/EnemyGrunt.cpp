#include "PreCompileHeader.h"
#include "EnemyGrunt.h"
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
			EnemyRenderer->ChangeAnimation("WALK");
			AggroDir(m_pCapsuleComp);
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
			AggroDir(m_pCapsuleComp);

		},
		[this]
		{
			m_f4TargetPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			m_f4WaitPos = GetTransform()->GetWorldPosition();
		}
	);
	SetFSM(EnemyGruntState::JUMP,
		[this]
		{
			EnemyRenderer->ChangeAnimation("JUMP_START");
			//m_f4HeightPos = CalJumpPos();
			m_f4HeightPos = AggroDir(m_pCapsuleComp);
			m_f4HeightPos.y = m_f4HeightPos.Size();
			float fDist = m_f4TargetPos.XYZDistance(m_f4WaitPos) * 0.8f;
			if (fDist>800.f)
			{
				fDist = 800.f;
			}
			m_f4HeightPos *= fDist;
		},
		[this](float Delta)
		{
			static float4 JumpDir;

			if (m_f4HeightPos.Size()<250.f)
			{
				EnemyRenderer->ChangeAnimation("JUMP_MAIN");
				if (true == EnemyRenderer->IsAnimationEnd())
				{
					SetNextState(EnemyGruntState::IDLE);
					return;
				}
			}

			if (true == EnemyRenderer->IsAnimationEnd()&& false == GetStateChecker())
			{
				//if ()
				//{
					EnemyRenderer->ChangeAnimation("JUMP_MAIN");
					SetStateCheckerOn();
					//StateChecker = true;
					//JumpDir = AggroDir(m_pCapsuleComp);
					//JumpDir.y = 1.0f;
					//m_pCapsuleComp->SetMoveSpeed(JumpDir * GRUNT_JUMP_SPEED);
					//return;
				//}
				//else
				//{
				//	if (true == m_pCapsuleComp->Jump(m_f4HeightPos))
				//	{
				//		SetNextState(EnemyGruntState::IDLE);
				//	};
				//	//attack
				//	//SetNextState(EnemyGruntState::IDLE);
				//}
			}
			if (true == GetStateChecker() &&true == m_pCapsuleComp->Jump(m_f4HeightPos,2.f))
			{
				SetNextState(EnemyGruntState::IDLE);
			};
			//if (true == StateChecker)
			//{
			//	m_pCapsuleComp->SetMoveSpeed(JumpDir * GRUNT_JUMP_SPEED);
			//}

		},
		[this]
		{
			m_pCapsuleComp->SetMoveSpeed(float4::ZERO);
		}
	);

	SetFSM(EnemyGruntState::HIT,
		[this]
		{
			AggroDir(m_pCapsuleComp);
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

float4 EnemyGrunt::CalJumpPos()
{
	float4 f4HeightPos = float4::Lerp(m_f4WaitPos,m_f4TargetPos,0.8f);
	float fHeight = m_f4WaitPos.XYZDistance(f4HeightPos);
	f4HeightPos.y += fHeight;
	return f4HeightPos;
}
