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
	m_pNaviRenderer->Off();


	m_pNaviComp = CreateComponent<PhysXTriangleComponent>();
	m_pNaviComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pNaviComp->CreatePhysXActors("Fortress_Navi_DC.fbx", true);
	m_pNaviComp->SetWorldPosWithParent(float4(0, 10000, 0), float4{ 0 , -135, 0 });
	m_pNaviComp->SetNavigation();
}

void Map_NaviMesh::Update(float _DeltaTime)
{
}

