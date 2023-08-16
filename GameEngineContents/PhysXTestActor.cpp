#include "PrecompileHeader.h"
#include "PhysXTestActor.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXBoxGeometryComponent.h"
#include "PhysXTestLevel.h"
PhysXTestActor::PhysXTestActor() 
{
}

PhysXTestActor::~PhysXTestActor() 
{
}

void PhysXTestActor::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("House1.fbx", "MeshTexture");

	float4 Scale = pRenderer->GetTransform()->GetLocalScale();
	pRenderer->GetTransform()->SetLocalScale(Scale * 10.0f);
	GetTransform()->SetLocalPosition(float4(0.f, 500.f, 0.f));


	std::shared_ptr<PhysXBoxGeometryComponent> pGeometryComp = CreateComponent<PhysXBoxGeometryComponent>();
	if (GetLevel()->DynamicThis<PhysXTestLevel>()!= nullptr)
	{
		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();
		pGeometryComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics,{10.f,10.f,10.f});
	}
}

void PhysXTestActor::Update(float _DeltaTime)
{
}

