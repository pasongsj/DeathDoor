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
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("_E_FIREPLANT_MESH.FBX", "ContentAniMeshDeffered");

	EnemyRenderer->CreateFBXAnimation("IDLE", "_E_FIREPLANT_IDLE.fbx", { 0.02f,true });
	EnemyRenderer->CreateFBXAnimation("BITE", "_E_FIREPLANT_BITE.fbx", { 0.02f,false });
	EnemyRenderer->CreateFBXAnimation("HIT", "_E_FIREPLANT_HIT.fbx", { 0.04f,false });
	EnemyRenderer->CreateFBXAnimation("DIE", "_E_FIREPLANT_DIE.fbx", { 0.02f,false });
	EnemyRenderer->ChangeAnimation("IDLE");
}




void EnemyFirePlant::Start()
{
	EnemyBase::Start();
	GetTransform()->SetLocalScale(float4::ONE * RENDERSCALE_FIREPLANT); // 임시 값조정 필요
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_FIREPLANT, DEFAULT_DIR_FIREPLANT);
		//m_pCapsuleComp->TurnOffGravity();
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic, PhysXFilterGroup::PlayerSkill);

	}
	SetFSMFUNC();

}
bool EnemyFirePlant::CheckAttack()
{
	UINT HitFromPlayer = static_cast<UINT>(isPhysXCollision);
	
	if ( 0 < (HitFromPlayer & static_cast<UINT>(PhysXFilterGroup::PlayerSkill)))
	{
		return true;
	}
	return false;
}

void EnemyFirePlant::Update(float _DeltaTime)
{
	//if ((isPhysXCollision & 1) == 1)
	//{
	//	int a = 0;
	//}
	//UINT playerDy = static_cast<UINT>(PhysXFilterGroup::PlayerSkill);
	//UINT ColPlayer = isPhysXCollision & playerDy;
	//if (0 < ColPlayer)
	//{
	//	int a = 0;
	//}
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
			if (true == CheckAttack())
			{
				SetNextState(EnemyFireFlowerState::HIT);
				return;
			}
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
 			AggroDir(m_pCapsuleComp, DEFAULT_DIR_FIREPLANT);
			// fire 투사체 발사 
		},
		[this](float Delta)
		{
			if (true == CheckAttack())
			{
				SetNextState(EnemyFireFlowerState::HIT);
				return;
			}
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
	
	SetFSM(EnemyFireFlowerState::HIT,
		[this]
		{
			EnemyRenderer->ChangeAnimation("HIT");
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