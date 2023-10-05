#include "PrecompileHeader.h"
#include "Crate.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

Crate::Crate()
{
}

Crate::~Crate()
{
}

void Crate::Start()
{
	InitComponent();
}

void Crate::Update(float _DeltaTime)
{
}

void Crate::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Crate.fbx", "ContentMeshDeffered");
	GetTransform()->SetWorldPosition(float4 { 400, 20 ,0 });

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);



	auto Test = m_pPhysXComponent->GetStatic()->getGlobalPose();

	int a = 0;
}
