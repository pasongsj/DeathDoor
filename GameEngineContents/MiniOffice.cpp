#include "PrecompileHeader.h"
#include "MiniOffice.h"

#include "PhysXBoxComponent.h"

MiniOffice::MiniOffice()
{
}

MiniOffice::~MiniOffice()
{
}

void MiniOffice::Start()
{
	InitComponent();
}

void MiniOffice::Update(float _DeltaTime)
{
}

void MiniOffice::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Post_Office.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 0.75f;
	// MeshScale *= 2.2f;

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return());
}
