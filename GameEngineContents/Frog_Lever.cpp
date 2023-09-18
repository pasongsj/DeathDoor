#include "PrecompileHeader.h"
#include "Frog_Lever.h"

#include "PhysXBoxComponent.h"


Frog_Lever::Frog_Lever()
{
}

Frog_Lever::~Frog_Lever()
{
}

void Frog_Lever::Start()
{
	InitComponent();
}

void Frog_Lever::Update(float _DeltaTime)
{
}

void Frog_Lever::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("lightStreetBase__1_.fbx", "MeshTexture");

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
