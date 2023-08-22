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

void PhysXTestPlane::Start()
{
	GetTransform()->SetLocalPosition({ 0.f,-100.f,0.f });
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("Ground_Mesh.fbx", "MeshTexture");

	float4 scale = pRenderer->GetMeshScale();
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);


	if (GetLevel()->DynamicThis<PhysXTestLevel>() != nullptr)
	{
		std::shared_ptr<PhysXBoxComponent> pBoxComp = CreateComponent<PhysXBoxComponent>();
		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();
		pBoxComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);
		pBoxComp->SetPositionSetFromParentFlag(true);

	}
}

void PhysXTestPlane::Update(float _DeltaTime)
{
}

