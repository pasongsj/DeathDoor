#include "PrecompileHeader.h"
#include "PhysXTestActor.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXBoxGeometryComponent.h"
#include "PhysXDynamicActorComponent.h"
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

	float4 scale = pRenderer->GetMeshScale();
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);


	pDynamicActorComp = CreateComponent <PhysXDynamicActorComponent>();
	//pGeometryComp = CreateComponent<PhysXBoxGeometryComponent>();

	if (GetLevel()->DynamicThis<PhysXTestLevel>()!= nullptr)
	{
		std::shared_ptr<PhysXTestLevel> pLevel = GetLevel()->DynamicThis<PhysXTestLevel>();

		pDynamicActorComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);



		//pGeometryComp->SetGravity(true);
		//pGeometryComp->SetRestitution(2.f);
		//pGeometryComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);
		//pGeometryComp->SetPositionSetFromParentFlag(true);
	}
}

void PhysXTestActor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("CamMoveLeft"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveRight"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveUp"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveDown"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * 500.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveBack"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * 500.f * _DeltaTime);
	}
};

