#include "PreCompileHeader.h"
#include "EnemyFirePlant.h"
#include "PhysXCapsuleComponent.h"

EnemyFirePlant::EnemyFirePlant()
{
}

EnemyFirePlant::~EnemyFirePlant()
{
}

void EnemyFirePlant::InitAniamtion()
{
	FlowerRender = CreateComponent<GameEngineFBXRenderer>();
	FlowerRender->SetFBXMesh("_E_FIREPLANT_MESH.FBX", "MeshAniTexture");

	FlowerRender->CreateFBXAnimation("IDLE", "_E_FIREPLANT_IDLE.fbx", { 0.02f,true });
	FlowerRender->CreateFBXAnimation("BITE", "_E_FIREPLANT_BITE.fbx", { 0.02f,false });
	FlowerRender->CreateFBXAnimation("DIE", "_E_FIREPLANT_DIE.fbx", { 0.02f,false });
	FlowerRender->ChangeAnimation("IDLE");
}

void EnemyFirePlant::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * 5000.0f); // 임시 값조정 필요
	// physx
	{
		//  임시 값조정 필요
		float4 scale = FlowerRender->GetMeshScale() * 0.0003f;
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(vscale, float4(-90.0f, 0.0f, 0.0f));
		m_pCapsuleComp->TurnOffGravity();
	}
	SetFSMFUNC();

}

void EnemyFirePlant::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}


void EnemyFirePlant::AggroMove()
{
	float4 PlayerDir = GetPlayerDir();
	float4 CalRot = float4::ZERO;
	CalRot.x = 90.0f;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, PlayerDir);
	m_pCapsuleComp->SetRotation(-CalRot);
}


void EnemyFirePlant::SetFSMFUNC()
{
	InitFSM(EnemyFireFlowerState::MAX);

	SetChangeFSMCallBack([this]
		{

		});
	SetFSM(EnemyFireFlowerState::IDLE,
		[this]
		{
			FlowerRender->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (true == InRangePlayer(1000.0f))
			{
				SetNextState(EnemyFireFlowerState::BITE);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyFireFlowerState::BITE,
		[this]
		{
			FlowerRender->ChangeAnimation("BITE");
			AggroMove();
			// fire 투사체 발사 
		},
		[this](float Delta)
		{
			if (true == FlowerRender->IsAnimationEnd())
			{
				SetNextState(EnemyFireFlowerState::IDLE);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(EnemyFireFlowerState::DIE,
		[this]
		{
			FlowerRender->ChangeAnimation("DIE");
		},
		[this](float Delta)
		{
			if (true == FlowerRender->IsAnimationEnd())
			{
				// Die
				return;
			}
		},
		[this]
		{
			
		}
	);


}