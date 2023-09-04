#include "PrecompileHeader.h"
#include "Map_PhysXActor.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

#include "PhysXBoxComponent.h"
#include "PhysXDynamicActorComponent.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXConvexComponent.h"
#include "PhysXTriangleComponent.h"
#include "PhysXSphereComponent.h"

#include "PhysXTestLevel.h"
#include "MapTestLevel.h"

Map_PhysXActor::Map_PhysXActor()
{
}

Map_PhysXActor::~Map_PhysXActor()
{
}

void Map_PhysXActor::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("Player.fbx", "MeshTexture");


	float4 scale = pRenderer->GetMeshScale();
	//pRenderer->GetTransform()->AddLocalPosition(float4(0.f, -scale.hy(), 0.f));
	physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);

	//m_pConvexComp = CreateComponent <PhysXConvexComponent>();
	//m_pTriangleComp = CreateComponent <PhysXTriangleComponent>();
	//m_pDynamicActorComp = CreateComponent <PhysXDynamicActorComponent>();
	//m_pGeometryComp = CreateComponent<PhysXBoxGeometryComponent>();
	m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
	//m_pSphereComp = CreateComponent<PhysXSphereComponent>();
	//m_pSphereComp->SetPhysxMaterial(100.f, 100.f, 0.f);
	//m_pSphereComp->CreatePhysXActors(pLevel->GetScene(), pLevel-//>GetPhysics(), vscale);
	//m_pSphereComp->GetDynamic()->setMass(1.f);
	//m_pSphereComp->TurnOnSpeedLimit();

	m_pCapsuleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pCapsuleComp->CreatePhysXActors(vscale);
	//m_pCapsuleComp->TurnOnSpeedLimit();
	//m_pConvexComp->CreatePhysXActors("Armature.fbx", pLevel->m_pScene, pLevel->m_pPhysics, pLevel->m_pCooking, true, vscale);
	//m_pTriangleComp->CreatePhysXActors("Armature.fbx", pLevel->m_pScene, pLevel->m_pPhysics, pLevel->m_pCooking,true ,vscale);
	//m_pDynamicActorComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);

	//m_pGeometryComp->SetGravity(true);
	//m_pGeometryComp->SetRestitution(2.f);
	//m_pGeometryComp->CreatePhysXActors(pLevel->m_pScene, pLevel->m_pPhysics, vscale);
	//m_pGeometryComp->SetPositionSetFromParentFlag(true);
	
	CreatePhysXComponent();
}

void Map_PhysXActor::CreatePhysXComponent()
{
	SetPhysXComponent(m_pCapsuleComp);
}
