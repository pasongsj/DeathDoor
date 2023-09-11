#include "PreCompileHeader.h"
#include "EnemyBat.h"
#include "PhysXCapsuleComponent.h"



EnemyBat::EnemyBat()
{
}

EnemyBat::~EnemyBat()
{
}

void EnemyBat::InitAniamtion()
{
	BatRender = CreateComponent<GameEngineFBXRenderer>();
	BatRender->SetFBXMesh("_E_BAT_Black Variant_MESH.FBX", "MeshAniTexture");

	BatRender->CreateFBXAnimation("IDLE", "_E_BAT_Black Variant_IDLE.fbx", { 0.02f,true });
	//BatRender->CreateFBXAnimation("FLY", "_E_BAT_Black Variant_FLY.fbx", { 0.02f,true });
	BatRender->CreateFBXAnimation("BITE", "_E_BAT_Black Variant_BITE.fbx", { 0.02f,false });
	BatRender->CreateFBXAnimation("IDLE_FLOOR", "_E_BAT_Black Variant_IDLE_FLOOR.fbx", { 0.02f,true });
	BatRender->CreateFBXAnimation("SHOCK", "_E_BAT_Black Variant_SHOCK.fbx", { 0.02f,false });
	BatRender->ChangeAnimation("IDLE");
}

void EnemyBat::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * 20.0f);

	// physx
	{
		float4 scale = BatRender->GetMeshScale() * BatRender->GetTransform()->GetWorldScale() / BatRender->GetTransform()->GetLocalScale();
		// scale *= 2.0f;
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(vscale);
	}
	SetFSMFUNC();
	SetNextState(EnemyBatState::FLY);
}

void EnemyBat::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}

#define IDLEMOVEROT float4{0,10.0f,0}
#define BAT_MOVE_SPEED 200.0f

void EnemyBat::IdleMove(float _DeltaTime)
{
	static float IdleDir = 0.0f;
	IdleDir += _DeltaTime*100.0f;
	m_pCapsuleComp->SetRotation(float4{0,IdleDir ,0});
	m_pCapsuleComp->SetMoveSpeed(GetTransform()->GetLocalForwardVector() * BAT_MOVE_SPEED);

}

void EnemyBat::AggroMove(float _DeltaTime)
{
	float4 PlayerDir = GetPlayerDir();
	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, PlayerDir);
	m_pCapsuleComp->SetRotation(/*PlayerInitRotation*/ -CalRot);

	m_pCapsuleComp->SetMoveSpeed(PlayerDir * BAT_MOVE_SPEED);

}



void EnemyBat::SetFSMFUNC()
{
	InitFSM(EnemyBatState::MAX);

	SetChangeFSMCallBack([this]
		{

		});



	SetFSM(EnemyBatState::IDLE,
		[this]
		{
			BatRender->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (true == InRangePlayer(1000.0f))
			{
				SetNextState(EnemyBatState::FLY);
				return;
			}
			IdleMove(Delta);
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBatState::FLY,
		[this]
		{
			//BatRender->ChangeAnimation("FLY");

		},
		[this](float Delta)
		{
			if (true == InRangePlayer(300.0f))
			{
				SetNextState(EnemyBatState::BITE);
				return;
			}
			if (false == InRangePlayer(1000.0f))
			{
				SetNextState(EnemyBatState::IDLE);
			}
			AggroMove(Delta);
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBatState::BITE,
		[this]
		{
			BatRender->ChangeAnimation("BITE");
		},
		[this](float Delta)
		{
			if (true == BatRender->IsAnimationEnd())
			{
				SetNextState(EnemyBatState::IDLE);
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBatState::IDLE_FLOOR,
		[this]
		{
			BatRender->ChangeAnimation("IDLE_FLOOR");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);

	SetFSM(EnemyBatState::SHOCK,
		[this]
		{
			BatRender->ChangeAnimation("SHOCK");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
