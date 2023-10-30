#include "PrecompileHeader.h"
#include "SecretTile.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

#include "FrogBossLevel.h"

SecretTile::SecretTile()
{
}

SecretTile::~SecretTile()
{
}



void SecretTile::InActive()
{
	m_bIsActive = false;
	m_pRenderer->Off();
	Off();
	
	m_pPhysXComponent->Death();
	m_pPhysXComponent = nullptr;
}

void SecretTile::Active()
{
	m_bIsActive = true; 
	m_pRenderer->On();
	On();
	
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	// 여기서 프로그 보스레벨이면 45도 회전시킨다. 
	std::shared_ptr<FrogBossLevel> CurLevel = GetLevel()->DynamicThis<FrogBossLevel>();
	if (CurLevel != nullptr)
	{
		m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4 { 0, -45, 0 }, true);
	}
	else if(CurLevel == nullptr)
	{
		m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	}

	m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y , 0.0f });
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	m_TileSize = static_cast<float>(MeshScale.x * sqrt(2) / 2.0f);
}

void SecretTile::Start()
{
	InitComponent();
}

void SecretTile::Update(float _DeltaTime)
{
	
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
