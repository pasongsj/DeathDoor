#include "PrecompileHeader.h"
#include "FlowerPot.h"

#include "PhysXBoxComponent.h"

FlowerPot::FlowerPot()
{
}

FlowerPot::~FlowerPot()
{
}

void FlowerPot::Start()
{
	InitComponent();
}

void FlowerPot::Update(float _DeltaTime)
{
}

void FlowerPot::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("plantBase1__2_.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.z *= 1.65f;
	MeshScale.x *= 0.9f;
	//MeshScale *= 0.85f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
}
