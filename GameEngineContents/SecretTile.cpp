#include "PrecompileHeader.h"
#include "SecretTile.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

SecretTile::SecretTile()
{
}

SecretTile::~SecretTile()
{
}

void SecretTile::Start()
{
	InitComponent();
}

void SecretTile::Update(float _DeltaTime)
{
}

// 배율 임시 
void SecretTile::InitComponent()
{
	GetTransform()->SetWorldPosition(float4{ -450, 5, 0 });

	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("FrogTile.fbx", "ContentMeshDeffered");
	float4 Scale = m_pRenderer->GetTransform()->GetLocalScale();
	Scale.x *= 1.2f;
	Scale.z *= 1.2f;

	m_pRenderer->GetTransform()->SetLocalScale(Scale);

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= 1.2f;
	MeshScale.z *= 1.2f;


	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
}
