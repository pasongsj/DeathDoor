#include "PreCompileHeader.h"
#include "EnemyFirePlant.h"
#include "PhysXCapsuleComponent.h"
#define FirePlantDefaultDir float4(90.0f,0.0f,0.0f)

EnemyFirePlant::EnemyFirePlant()
{
}

EnemyFirePlant::~EnemyFirePlant()
{
}

void EnemyFirePlant::InitAniamtion()
{
	EnemyRenderer = CreateComponent<GameEngineFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_FIREPLANT_MESH.FBX", "MeshAniTexture");

	EnemyRenderer->CreateFBXAnimation("IDLE", "_E_FIREPLANT_IDLE.fbx", { 0.02f,true });
	EnemyRenderer->CreateFBXAnimation("BITE", "_E_FIREPLANT_BITE.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("DIE", "_E_FIREPLANT_DIE.fbx", { 0.02f,false });
	EnemyRenderer->ChangeAnimation("IDLE");
}

void EnemyFirePlant::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * 5000.0f); // 임시 값조정 필요
	// physx
	{
		//  임시 값조정 필요
		float4 scale = EnemyRenderer->GetMeshScale() * 0.0003f;
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


void EnemyFirePlant::SetFSMFUNC()
{
	InitFSM(EnemyFireFlowerState::MAX);

	SetChangeFSMCallBack([this]
		{

		});
	SetFSM(EnemyFireFlowerState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
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
			EnemyRenderer->ChangeAnimation("BITE");
			AggroDir(m_pCapsuleComp, FirePlantDefaultDir);
			// fire 투사체 발사 
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
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
			EnemyRenderer->ChangeAnimation("DIE");
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
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