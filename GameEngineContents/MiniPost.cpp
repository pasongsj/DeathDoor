#include "PrecompileHeader.h"
#include "MiniPost.h"

#include "PhysXBoxComponent.h"

MiniPost::MiniPost()
{
}

MiniPost::~MiniPost()
{
}

void MiniPost::Start()
{
	InitComponent();
}

void MiniPost::Update(float _DeltaTime)
{
}

void MiniPost::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Post.fbx", "MeshTexture");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return());
}
