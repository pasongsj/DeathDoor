#include "PrecompileHeader.h"
#include "CullingTrigger.h"

#include "ContentFBXRenderer.h"
#include "PhysXBoxComponent.h"

CullingTrigger::CullingTrigger()
{
}

CullingTrigger::~CullingTrigger()
{
}

void CullingTrigger::Start()
{
	InitComponent();
}

void CullingTrigger::Update(float _DeltaTime)
{
}

void CullingTrigger::InitComponent()
{	
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	// 네모난메쉬 아무거나 가져다 쓸거 
	m_pRenderer->SetFBXMesh("Ladder.fbx", "ContentMeshDeffered");

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);
}
