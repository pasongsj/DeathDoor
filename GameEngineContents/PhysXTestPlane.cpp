#include "PrecompileHeader.h"
#include "PhysXTestPlane.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "PhysXBoxGeometryComponent.h"
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
	float4 scale = pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);

	std::shared_ptr<PhysXBoxGeometryComponent> pGeometryComp = CreateComponent<PhysXBoxGeometryComponent>();
	if (GetLevel()->DynamicThis<PhysXTestLevel>() != nullptr)
	{
		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();
		pGeometryComp->SetGravity(false);
		pGeometryComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);

	}
}

void PhysXTestPlane::Update(float _DeltaTime)
{
}

