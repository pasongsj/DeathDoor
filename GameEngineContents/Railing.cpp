#include "PrecompileHeader.h"
#include "Railing.h"

#include "PhysXBoxComponent.h"

#include "ContentFBXRenderer.h"

Railing::Railing()
{
}

Railing::~Railing()
{
}

void Railing::Start()
{
	InitComponent();
}

void Railing::Update(float _DeltaTime)
{
}

void Railing::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("railing.fbx", "ContentMeshDeffered");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= 0.15f;
	MeshScale.y *= 1.5f;
	MeshScale.z *= 2.0f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
