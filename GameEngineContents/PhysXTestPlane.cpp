#include "PrecompileHeader.h"
#include "PhysXTestPlane.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "PhysXBoxComponent.h"
#include "PhysXTestLevel.h"

PhysXTestPlane::PhysXTestPlane() 
{
}

PhysXTestPlane::~PhysXTestPlane() 
{
}

int PhysXTestPlane::Count=0;

void PhysXTestPlane::Start()
{
	GetTransform()->SetLocalPosition({ 0.f,-100.f,0.f });
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("Ground_Mesh.fbx", "MeshTexture");

	float4 scale = pRenderer->GetMeshScale();
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);

	m_pBoxComp = CreateComponent<PhysXBoxComponent>();

	m_pBoxComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	if (Count != 0)
	{
		//m_pBoxComp->SetObjectObstacle();
		GetTransform()->AddWorldRotation(float4{ 0, 45, 10 });
	}
	m_pBoxComp->CreatePhysXActors(vscale, GetTransform()->GetWorldRotation());
	++Count;

}

void PhysXTestPlane::Update(float _DeltaTime)
{
}

