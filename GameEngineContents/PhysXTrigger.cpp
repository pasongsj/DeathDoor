#include "PrecompileHeader.h"
#include "PhysXTrigger.h"
#include "PhysXBoxComponent.h"

PhysXTrigger::PhysXTrigger() 
{
}

PhysXTrigger::~PhysXTrigger() 
{
}

void PhysXTrigger::Start()
{
	GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("Ground_Mesh.fbx", "MeshTexture");
	pRenderer->GetTransform()->SetLocalScale({ 0.1f, 0.1f, 0.1f });
	float4 scale = pRenderer->GetMeshScale()*0.1f;
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);

	m_pBoxCompo = CreateComponent<PhysXBoxComponent>();
	m_pBoxCompo->CreatePhysXActors(vscale,float4::ZERO,true);

	m_pBoxCompo->SetFilterData(PhysXFilterGroup::Obstacle);
	m_pBoxCompo->SetTrigger();
	
}

void PhysXTrigger::Update(float _DeltaTime)
{
}

