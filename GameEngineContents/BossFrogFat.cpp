#include "PreCompileHeader.h"
#include "BossFrogFat.h"

BossFrogFat::BossFrogFat()
{
}

BossFrogFat::~BossFrogFat()
{
}

void BossFrogFat::Start()
{
	EnemyBase::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_MAGE * 3.0f);
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
	}
}

void BossFrogFat::Update(float _DeltaTime)
{
	AnimationBoneData BoneData = EnemyRenderer->GetBoneData("_FROG_SEPTRE_BONE");
	WeaponRenderer->GetTransform()->SetLocalPosition(WeaponPivotPos + BoneData.Pos);
	WeaponRenderer->GetTransform()->SetLocalRotation(WeaponPivotRot + BoneData.RotEuler);
	FSMObjectBase::Update(_DeltaTime);
}

void BossFrogFat::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("FROG_FAT_MESH.FBX", "ContentAniMeshDeffered");


	EnemyRenderer->CreateFBXAnimation("DIE_LAND", "FROG_FAT_DIE_LAND.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("DIE_STANDING", "FROG_FAT_DIE_STANDING.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("IDLE", "FROG_FAT_IDLE.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("FAT_JUMP", "FROG_FAT_JUMP.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("JUMP_SCREAM", "FROG_FAT_JUMP_SCREAM.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SHOOT", "FROG_FAT_SHOOT.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SUCK", "FROG_FAT_SUCK.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB", "FROG_FAT_SUCK_BOMB.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_GETUP", "FROG_FAT_SUCK_BOMB_GETUP.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_LOOP", "FROG_FAT_SUCK_BOMB_LOOP.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("TILT", "FROG_FAT_TILT.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("TILT_GRABBED", "FROG_FAT_TILT_GRABBED.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("TILT_JUMP", "FROG_FAT_TILT_JUMP.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("TURN", "FROG_FAT_TURN.fbx", { 1.0f / 30, false });
	EnemyRenderer->GetTransform()->SetLocalScale(float4::ONE * 100.0f);

	WeaponRenderer = CreateComponent<ContentFBXRenderer>();
	WeaponRenderer->SetFBXMesh("FROG_WEAPONMESH.FBX", "ContentMeshDeffered");
	WeaponRenderer->GetTransform()->SetParent(EnemyRenderer->GetTransform());
	WeaponRenderer->GetTransform()->SetLocalScale(float4::ONE * 1.4f);
	WeaponRenderer->SetGlowToUnit(1, 0);
	WeaponRenderer->SetUnitColor(1, 0, { 244.0f / 255.0f, 74.0f / 255.0f, 96.0f / 255.0f , 1.0f }, 5.0f);
	EnemyRenderer->ChangeAnimation("IDLE");

}

void BossFrogFat::SetFSMFUNC()
{
	InitFSM(BossFrogFatState::MAX);

	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});



	SetFSM(BossFrogFatState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);

}
