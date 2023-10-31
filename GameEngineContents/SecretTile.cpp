#include "PrecompileHeader.h"
#include "SecretTile.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

#include "FrogBossLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

SecretTile::SecretTile()
{
}

SecretTile::~SecretTile()
{
}


void SecretTile::InActive()
{
	OffShake();
	m_bIsActive = false;
	m_pRenderer->Off();
	
	m_pPhysXComponent->Death();
	m_pPhysXComponent = nullptr;
}

void SecretTile::Active()
{
	m_bIsActive = true; 
	m_pRenderer->On();
	
	GetTransform()->SetLocalRotation(float4{ 0, 0, 0 });
	
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERO, true);

	m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y , 0.0f });
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	float4 Test = GetTransform()->GetLocalRotation();

	// 타일사이즈저장
	m_TileSize = static_cast<float>(MeshScale.x * sqrt(2) / 2.0f);
}

void SecretTile::TileShake(float _DeltaTime)
{
	if (0.0f >= m_fShakeTime)
	{
 		m_bShake = false;
		m_fShakeTime = 2.0f;

		InActive();
		return;
	}

	// shake 코드치면 된다~ 부들부들대게 만들면 되는데~~ 
	m_fShakeTime -= _DeltaTime;

	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);
	float RandomRotValue = GameEngineRandom::MainRandom.RandomFloat(-7.0f , 7.0f);
	if (RandomValue == 1)
	{
		GetTransform()->SetLocalRotation(float4{ RandomRotValue, 0, 0 });
	}

	else if (RandomValue == 2)
	{
		GetTransform()->SetLocalRotation(float4{ 0 , 0, RandomRotValue });
	}
}

void SecretTile::OffShake()
{
	m_bShake = false;
	m_fShakeTime = 2.0f;
	// GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });
}

void SecretTile::Start()
{
	InitComponent();
}

void SecretTile::Update(float _DeltaTime)
{
	if (true == m_bShake)
	{
		TileShake(_DeltaTime);
	}
}

void SecretTile::InitComponent()
{
	GetTransform()->SetLocalPosition(float4{ 0.0f , 0.1f , 0.0f });

	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("FrogTile.fbx", "ContentMeshDeffered");

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y , 0.0f });
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	m_TileSize = static_cast<float>(MeshScale.x * sqrt(2) / 2.0f);
}
