#include "PrecompileHeader.h"
#include "StreetLamp.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

StreetLamp::StreetLamp()
{
}

StreetLamp::~StreetLamp()
{
}

void StreetLamp::Start()
{
	InitComponent();
}

void StreetLamp::Update(float _DeltaTime)
{
}

void StreetLamp::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("GiantStreetLamp.fbx", "ContentMeshDeffered");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= 2.2f;
	MeshScale.z *= 2.2f;
	
	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
