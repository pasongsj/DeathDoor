#include "PrecompileHeader.h"
#include "Transform_Wall.h"

#include "PhysXBoxComponent.h"

Transform_Wall::Transform_Wall()
{
}

Transform_Wall::~Transform_Wall()
{
}



void Transform_Wall::Start()
{
	InitComponent();
}

void Transform_Wall::Update(float _DeltaTime)
{
}

// 얘는 여기서 생성만해주고 세팅해서 사용하도록 
// 메쉬는 그냥 fence fbx 사용
void Transform_Wall::InitComponent()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Fence.fbx", "MeshTexture");
	m_pRenderer->Off();

	m_pComp = CreateComponent<PhysXBoxComponent>();
	m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
}

void Transform_Wall::Set_MeshRatio(float4& _Ratio)
{
	if (nullptr == m_pComp)
	{
		m_pComp = CreateComponent<PhysXBoxComponent>();
		m_pComp->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	}
	
	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale.x *= _Ratio.x;
	MeshScale.y *= _Ratio.y;
	MeshScale.z *= _Ratio.z;

	// 임시로 dynamic
	m_pComp->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL/*, true*/);
}