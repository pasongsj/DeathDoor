#include "PrecompileHeader.h"
#include "Map_Fortress.h"

#include "FortressLevel.h"

#include "ContentFBXRenderer.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"

#include "SecretTile.h"
#include "Crate.h"
#include "Ladder.h"


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
	m_pRenderer_Part1 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part1->SetFBXMesh("Fortress_Part1.fbx", "ContentMesh");
	m_pRenderer_Part1->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part1->GetTransform()->SetLocalPosition(float4 { -8480, 140, -7360 });
	
	m_pRenderer_Part2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part2->SetFBXMesh("Fortress_Part2.fbx", "ContentMesh");
	m_pRenderer_Part2->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part2->GetTransform()->SetLocalPosition(float4{ -8334, 100, -6458 });

	m_pRenderer_Part3 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part3->SetFBXMesh("Fortress_Part3.fbx", "ContentMesh");
	m_pRenderer_Part3->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part3->GetTransform()->SetLocalPosition(float4{ -3844, 100 , -12898 });



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
	std::shared_ptr<Ladder> NewLadder = GetLevel()->CreateActor<Ladder>();
	NewLadder->GetTransform()->SetWorldPosition(float4 { 200, 200, 0 });
	
}

void Map_Fortress::Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel)
{
}
