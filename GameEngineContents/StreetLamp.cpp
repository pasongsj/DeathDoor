#include "PrecompileHeader.h"
#include "StreetLamp.h"

#include "PhysXBoxComponent.h"

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
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("GiantStreetLamp.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 2.2f;
	
	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return());
}
