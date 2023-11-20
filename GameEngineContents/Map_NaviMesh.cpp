#include "PrecompileHeader.h"
#include "Map_NaviMesh.h"

#include "ContentFBXRenderer.h"

#include "PhysXTriangleComponent.h"
#include "PhysXControllerComponent.h"
#include "Player.h"

Map_NaviMesh* Map_NaviMesh::NaviMesh = nullptr;

Map_NaviMesh::Map_NaviMesh() 
{
	NaviMesh = this;
}

Map_NaviMesh::~Map_NaviMesh() 
{
}

void Map_NaviMesh::Start()
{
	if (false == GameEngineInput::IsKey("G"))
	{
		GameEngineInput::CreateKey("G", 'G');	

	}
	m_pNaviRenderer = CreateComponent<ContentFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Fortress_Navi_DC.fbx", "ContentMeshDeffered");
	m_pNaviRenderer->GetTransform()->SetWorldPosition(float4(0,10000,0));
	m_pNaviRenderer->Off();

	m_pWallRenderer = CreateComponent<ContentFBXRenderer>();
	m_pWallRenderer->SetFBXMesh("Fortress_Navi_DC_Wall_Test.fbx", "ContentMeshDeffered");
	m_pWallRenderer->GetTransform()->SetWorldPosition(float4(0, 10000, 0));
	m_pWallRenderer->Off();

	m_pNaviComp = CreateComponent<PhysXTriangleComponent>();
	m_pNaviComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pNaviComp->CreatePhysXActors("Fortress_Navi_DC.fbx", true);
	m_pNaviComp->SetWorldPosWithParent(float4(0, -10000, 0), float4{ 0 , -135, 0 });
	m_pNaviComp->SetNavigation();
	m_pNaviComp->SetFilterData(PhysXFilterGroup::NaviMesh);

	std::shared_ptr<GameEngineActor> WallActor = GetLevel()->CreateActor<GameEngineActor>();
	std::shared_ptr<PhysXTriangleComponent>WallComp = WallActor->CreateComponent<PhysXTriangleComponent>();
	WallComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	WallComp->CreatePhysXActors("Fortress_Navi_DC_Wall_Test.fbx", true);
	WallComp->SetWorldPosWithParent(float4(0, -10000, 0), float4{ 0 , -135, 0 });
	WallComp->SetFilterData(PhysXFilterGroup::NaviMesh);

}

void Map_NaviMesh::Update(float _DeltaTime)
{
	if (nullptr != m_pNaviRenderer && nullptr != m_pWallRenderer && true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
		if (true == m_pNaviRenderer->IsUpdate() && true == m_pWallRenderer->IsUpdate())
		{
			m_pWallRenderer->Off();
			m_pNaviRenderer->Off();
		}
		else
		{
			m_pWallRenderer->On();
			m_pNaviRenderer->On();
		}
	}
}

