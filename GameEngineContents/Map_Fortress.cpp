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
	m_pRenderer_Part1->CalculateUnitPos();
	
	m_pRenderer_Part2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part2->SetFBXMesh("Fortress_Part2.fbx", "ContentMesh");
	m_pRenderer_Part2->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part2->GetTransform()->SetLocalPosition(float4{ -8334, 100, -6458 });
	m_pRenderer_Part2->CalculateUnitPos();

	m_pRenderer_Part3 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part3->SetFBXMesh("Fortress_Part3.fbx", "ContentMesh");
	m_pRenderer_Part3->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part3->GetTransform()->SetLocalPosition(float4{ -3844, 100 , -12898 });
	m_pRenderer_Part3->CalculateUnitPos();

	auto AllUnit = m_pRenderer_Part3->GetAllRenderUnit();
	auto UnTextureUnit = m_pRenderer_Part3->GetUnTexturedUnit();
	
	AllUnit[47][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	AllUnit[48][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	AllUnit[49][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");

	// uv 박살 , 이후 수정필요 
	AllUnit[50][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	// AllUnit[50][0]->UVdata = { 0.07f, 0.07f, 0.0f, 0.0f };
	AllUnit[50][1]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	AllUnit[50][2]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");

	m_pRenderer_Part4 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part4->SetFBXMesh("Fortress_Part4.fbx", "ContentMesh");
	m_pRenderer_Part4->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part4->GetTransform()->SetLocalPosition(float4{ -6474, 190 , -12078 });
	m_pRenderer_Part4->CalculateUnitPos();

	m_pRenderer_Part5 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part5->SetFBXMesh("Fortress_Part5.fbx", "ContentMesh");
	m_pRenderer_Part5->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part5->GetTransform()->SetLocalPosition(float4{ -4464, 320 , -15492 });
	m_pRenderer_Part5->CalculateUnitPos();

	m_pRenderer_Part6 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part6->SetFBXMesh("Fortress_Part6.fbx", "ContentMesh");
	m_pRenderer_Part6->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part6->GetTransform()->SetLocalPosition(float4{ -5222, 574 , -14561 });
	m_pRenderer_Part6->CalculateUnitPos();



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
	
	
}

void Map_Fortress::Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel)
{
}
