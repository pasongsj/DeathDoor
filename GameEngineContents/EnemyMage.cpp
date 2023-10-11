#include "PreCompileHeader.h"
#include "EnemyMage.h"
#include "Player.h"
#include <GameEngineBase/GameEngineRandom.h>


EnemyMage::EnemyMage() 
{
}

EnemyMage::~EnemyMage() 
{
}

void EnemyMage::InitAniamtion()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_MAGE_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "_E_MAGE_IDLE.fbx", { 0.02f,true });
	EnemyRenderer->CreateFBXAnimation("SHOOT", "_E_MAGE_SHOOT.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("TELEPORT", "_E_MAGE_TELEPORT.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("TELEPORT_IN", "_E_MAGE_TELEPORT.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("DEATH", "_E_MAGE_DEATH.fbx", { 0.02f,false });
	//_E_MAGE_SHOOT_THREE.fbx
	//_E_MAGE_SPIRAL.fbx

	EnemyRenderer->ChangeAnimation("IDLE");
	
	float4 f4Scale = EnemyRenderer->GetMeshScale();
	m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
	m_pCapsuleComp->CreatePhysXActors(float4(50, 200, 50));
	m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	m_pCapsuleComp->TurnOffGravity();
}



void EnemyMage::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_MAGE);

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_MAGE);
	}
	SetFSMFUNC();
}

void EnemyMage::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}



void EnemyMage::TeleportRandPos()
{
	m_bPosSet = false;
	float4 f4PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 f4GridStart = float4(f4PlayerPos.x - m_fTeleportRange, f4PlayerPos.z - m_fTeleportRange);
	float4 f4GridEnd = float4(f4PlayerPos.x + m_fTeleportRange, f4PlayerPos.z + m_fTeleportRange);

	int iVecSize = static_cast<int>(m_fTeleportRange * 2.f / m_fGridRange);
	vec_RandGrid.reserve(iVecSize * iVecSize);
	for (size_t i = 0; i < iVecSize; i++)
	{
		for (size_t j = 0; j < iVecSize; j++)
		{
			vec_RandGrid.push_back(float4(f4GridStart.x + m_fGridRange * i, f4GridStart.z + m_fGridRange * j));
		}
	}

	while (false == m_bPosSet)
	{
		int RandIndex = GameEngineRandom::MainRandom.RandomInt(0, vec_RandGrid.size()-1);

		float4 ResultPos = vec_RandGrid[RandIndex]; 
		ResultPos.x += m_fGridRange * 0.5f;
		ResultPos.z += m_fGridRange * 0.5f;
		ResultPos.y = f4PlayerPos.y+10.f;

		float4 RayCastPos = float4::ZERO;

		bool bGround = m_pCapsuleComp->RayCast(ResultPos, float4::DOWN, RayCastPos,100.f);

		if (bGround == false)
		{
			bGround = m_pCapsuleComp->RayCast(ResultPos, float4::DOWN, RayCastPos, 100.f);
			if (bGround == false)
			{
				m_bPosSet = true;
				m_pCapsuleComp->SetWorldPosWithParent(f4PlayerPos+float4(10,10));
			}
			else
			{
				m_bPosSet = true;
				m_pCapsuleComp->SetWorldPosWithParent(ResultPos);
			}
		}
		else
		{
			m_bPosSet = true;
			m_pCapsuleComp->SetWorldPosWithParent(ResultPos);
		}
	}
	

}
void EnemyMage::SetFSMFUNC()
{
	InitFSM(EnemyMageState::MAX);

	SetChangeFSMCallBack([this]
		{

		});



	SetFSM(EnemyMageState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (true == InRangePlayer(1000.0f))
			{
				SetNextState(EnemyMageState::SHOOT);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyMageState::SHOOT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SHOOT");
			AggroDir(m_pCapsuleComp);
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (false == InRangePlayer(1000.0f)) // 1500 이상으로 멀어진다면
				{
					SetNextState(EnemyMageState::TELEPORT);
					return;
				}
				SetNextState(EnemyMageState::IDLE);
			}

		},
		[this]
		{
		}
	);

	SetFSM(EnemyMageState::TELEPORT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("TELEPORT");
		},
		[this](float Delta)
		{
			TeleportRandPos();
			SetNextState(EnemyMageState::TELEPORT_IN);
		},
		[this]
		{
		}
	);

	SetFSM(EnemyMageState::TELEPORT_IN,
		[this]
		{
			EnemyRenderer->ChangeAnimation("TELEPORT_IN");
			AggroDir(m_pCapsuleComp);
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(EnemyMageState::SHOOT);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyMageState::DEATH,
		[this]
		{
			EnemyRenderer->ChangeAnimation("DEATH");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}