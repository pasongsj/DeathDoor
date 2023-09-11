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
	pRenderer->GetTransform()->SetLocalScale({ 0.1, 0.1, 0.1 });
	float4 scale = pRenderer->GetMeshScale();
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);

	m_pBoxComp = CreateComponent<PhysXBoxComponent>();
	m_pBoxComp->SetObjectObstacle();
	m_pBoxComp->CreatePhysXActors(vscale,float4::ZERO,true);
	
	m_pBoxComp->SetTrigger();
	
}

void PhysXTrigger::Update(float _DeltaTime)
{
}

