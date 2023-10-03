#include "PrecompileHeader.h"
#include "SemiCircleTable.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"


SemiCircleTable::SemiCircleTable()
{
}

SemiCircleTable::~SemiCircleTable()
{
}

void SemiCircleTable::Start()
{
	InitComponent();
}

void SemiCircleTable::Update(float _DeltaTime)
{
}

void SemiCircleTable::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Pipe.fbx", "ContentMeshDeffered");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	// MeshScale *= 1.2f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
