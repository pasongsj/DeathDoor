#include "PrecompileHeader.h"
#include "Fountain.h"
#include "PhysXBoxComponent.h"


Fountain::Fountain()
{
}

Fountain::~Fountain()
{
}

void Fountain::Start()
{
	InitComponent();
}

void Fountain::Update(float _DeltaTime)
{
}

void Fountain::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Fountain__1_.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 0.9f;
	// MeshScale *= 2.2f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return());
	
}
