#include "PrecompileHeader.h"
#include "Conveyor.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

Conveyor::Conveyor()
{
}

Conveyor::~Conveyor()
{
}

void Conveyor::Start()
{
	InitComponent();
}

void Conveyor::Update(float _DeltaTime)
{
}

void Conveyor::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Conveyor.fbx", "ContentMeshDeffered");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= 0.25f;
	MeshScale.z *= 1.15f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
