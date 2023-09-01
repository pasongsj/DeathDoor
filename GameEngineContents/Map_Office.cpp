#include "PrecompileHeader.h"
#include "Map_Office.h"

#include "PhysXBoxComponent.h"
#include "OfficeLevel.h"

Map_Office::Map_Office()
{
}

Map_Office::~Map_Office()
{
}

void Map_Office::Start()
{
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	// 얘는 Map_Office 세팅 완료 후에 해당 fbx로 변경할거임
	m_pRenderer->SetFBXMesh("Map_Office.fbx", "MeshTexture");

	m_pRenderer->GetTransform()->AddLocalRotation(float4{ 0 , -135 , 0 });

	auto Unit = m_pRenderer->GetAllRenderUnit();

	float4 UnitScale = m_pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;

	float4 scale = m_pRenderer->GetMeshScale();
	physx::PxVec3 vscale = UnitScale.PhysXVec3Return();


	if (GetLevel()->DynamicThis<OfficeLevel>() != nullptr)
	{
		m_pBoxComp = CreateComponent<PhysXBoxComponent>();
		m_pBoxComp->SetPhysxMaterial(0.f, 0.f, 0.f);
		std::shared_ptr<OfficeLevel> pLevel = GetLevel()->DynamicThis<OfficeLevel>();
		m_pBoxComp->CreatePhysXActors(vscale, GetTransform()->GetWorldRotation());
	}

}

void Map_Office::Update(float _DeltaTime)
{
	
}
