#include "PrecompileHeader.h"
#include "StreetLamp_2.h"

#include "PhysXBoxComponent.h"

StreetLamp_2::StreetLamp_2()
{
}

StreetLamp_2::~StreetLamp_2()
{
}

void StreetLamp_2::Start()
{
	InitComponent();
}

void StreetLamp_2::Update(float _DeltaTime)
{
}

void StreetLamp_2::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("lightStreetBase__1_.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	//MeshScale *= 2.2f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
