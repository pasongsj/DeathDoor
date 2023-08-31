#include "PrecompileHeader.h"
#include "TestMap.h"
#include "PhysXBoxComponent.h"
#include "MapTestLevel.h"


TestMap::TestMap()
{
}

TestMap::~TestMap()
{
}

void TestMap::Start()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Cube14.fbx", "MeshTexture");

	auto Unit = m_pRenderer->GetAllRenderUnit();
	
	float4 UnitScale = m_pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	
	float4 scale = m_pRenderer->GetMeshScale();
	physx::PxVec3 vscale = UnitScale.PhysXVec3Return();

	
	if (GetLevel()->DynamicThis<MapTestLevel>() != nullptr)
	{
		m_pBoxComp = CreateComponent<PhysXBoxComponent>();
		m_pBoxComp->SetPhysxMaterial(0.f, 0.f, 0.f);
		std::shared_ptr<MapTestLevel> pLevel = GetLevel()->DynamicThis<MapTestLevel>();
		m_pBoxComp->CreatePhysXActors(pLevel->GetScene(), pLevel->GetPhysics(), vscale, GetTransform()->GetWorldRotation());
	}

	
		
}

void TestMap::Update(float _DeltaTime)
{
	
}
