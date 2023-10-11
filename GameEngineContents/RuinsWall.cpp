#include "PrecompileHeader.h"
#include "RuinsWall.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

RuinsWall::RuinsWall()
{
}

RuinsWall::~RuinsWall()
{
}

void RuinsWall::Start()
{
	InitComponent();
}

void RuinsWall::Update(float _DeltaTime)
{
}

void RuinsWall::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Ruins_Wall.fbx", "ContentMeshDeffered");

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= 1.5f;

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y / 2.0f, 0.0f });
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
}
