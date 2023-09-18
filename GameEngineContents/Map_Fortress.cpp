#include "PrecompileHeader.h"
#include "Map_Fortress.h"

#include "FortressLevel.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"

#include "SecretTile.h"
#include "Crate.h"

Map_Fortress::Map_Fortress()
{
}

Map_Fortress::~Map_Fortress()
{
}

void Map_Fortress::NaviRenderSwitch()
{
	if (nullptr != m_pNaviRenderer)
	{
		if (true == m_pNaviRenderer->IsUpdate())
		{
			m_pNaviRenderer->Off();
		}
		else
		{
			m_pNaviRenderer->On();
		}
	}
}

void Map_Fortress::Start()
{
	// 컴포넌트 초기화 
	InitComponent();
	Create_StaticObject();
	Create_ActiveObject();
}

void Map_Fortress::Update(float _DeltaTime)
{
}


// 임시로 오피스로 적용 
void Map_Fortress::InitComponent()
{
	// 맵 렌더러 
	//m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	//m_pRenderer->SetFBXMesh("Fortress_FullMap.fbx", "MeshTexture");
	//// m_pRenderer->GetTransform()->SetLocalScale(float4{ -1, 1, 1 });
	//m_pRenderer->GetTransform()->SetLocalRotation(m_MapRot);
	//m_pRenderer->GetTransform()->SetLocalPosition(m_MapPos);
	// m_pRenderer->Off();
	// float4 Scale = m_pRenderer->GetTransform()->GetLocalScale();


	// 네비메쉬 위치확인용 렌더러 
	m_pNaviRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Fortrss_FullMap_Navi.fbx", "MeshTexture");
	m_pNaviRenderer->GetTransform()->SetLocalRotation(m_MapRot);
	m_pNaviRenderer->GetTransform()->SetLocalPosition(m_MapPos);
	//m_pNaviRenderer->Off();

	
	m_pTriangleComp = CreateComponent<PhysXTriangleComponent>();
	m_pTriangleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pTriangleComp->CreatePhysXActors("Fortrss_FullMap_Navi.fbx", true);
	m_pTriangleComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(m_MapRot, m_MapPos));
}

void Map_Fortress::Create_StaticObject()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}
}

void Map_Fortress::Create_ActiveObject()
{
	//test 
	std::shared_ptr<SecretTile> Tile = GetLevel()->CreateActor<SecretTile>();
	std::shared_ptr<Crate> Obj = GetLevel()->CreateActor<Crate>();
}

void Map_Fortress::Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel)
{
}
