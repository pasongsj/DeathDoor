#include "PrecompileHeader.h"
#include "Map_Office.h"

#include "OfficeLevel.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"


// static obj
#include "Transform_Wall.h"
#include "StreetLamp.h"
#include "StreetLamp_2.h"
#include "TrashCan.h"
#include "Fountain.h"
#include "SemiCircleTable.h"
#include "MiniOffice.h"
#include "FlowerPot.h"
#include "MiniDesk.h"
#include "Conveyor.h"
#include "Railing.h"
#include "Bench.h"
#include "MiniPost.h"

Map_Office::Map_Office()
{
}

Map_Office::~Map_Office()
{
}

void Map_Office::NaviRenderSwitch()
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

void Map_Office::Start()
{
	// 컴포넌트 초기화 
	InitComponent();
	Set_StaticObject();
	Set_ActiveObject();
}

void Map_Office::Update(float _DeltaTime)
{
}

void Map_Office::InitComponent()
{
	// 맵 렌더러 
	m_pRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pRenderer->SetFBXMesh("Map_Office.fbx", "MeshTexture");
	m_pRenderer->GetTransform()->SetLocalRotation(m_MapRot);

	// 네비메쉬 위치확인용 렌더러 
	m_pNaviRenderer = CreateComponent<GameEngineFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Map_Office_Navi.fbx", "MeshTexture");
	m_pNaviRenderer->GetTransform()->SetLocalRotation(m_MapRot);
	m_pNaviRenderer->GetTransform()->SetLocalPosition(m_MapPos);
	m_pNaviRenderer->Off();
	

	// float4 UnitScale = m_pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	// float4 scale = m_pRenderer->GetMeshScale();
	// physx::PxVec3 vscale = UnitScale.PhysXVec3Return();

	// 컴포넌트 
	m_pTriangleComp = CreateComponent<PhysXTriangleComponent>();
	m_pTriangleComp->SetObjectGround();
	m_pTriangleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pTriangleComp->CreatePhysXActors("Map_Office_Navi.fbx", true);
	m_pTriangleComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(m_MapRot, m_MapPos));
}



// 피직스 업데이트 후 전부 GetStatic 으로 변경예정 
void Map_Office::Set_StaticObject()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}

	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ 860, -780, -5020 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ 1994, -780, -5011 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ 3353 , -780, -5020 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ 3761 , -780, -5020 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ 3090 , -780, -5020 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Fountain> Obj = CurLevel->CreateActor<Fountain>();
		const float4 Pos = float4{ 150 , -272, -3914 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<SemiCircleTable> Obj = CurLevel->CreateActor<SemiCircleTable>();
		const float4 Pos = float4{ 2956, -274, -3304 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp> Obj = CurLevel->CreateActor<StreetLamp>();
		const float4 Pos = float4{ -794, -332, -3148 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<StreetLamp_2> Obj = CurLevel->CreateActor<StreetLamp_2>();
		const float4 Pos = float4{ 724, -314, -3130 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<MiniOffice> Obj = CurLevel->CreateActor<MiniOffice>();
		const float4 Pos = float4{ 1828, -251, -1931 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<FlowerPot> Obj = CurLevel->CreateActor<FlowerPot>();
		const float4 Pos = float4{ 783, -215, -1887 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<MiniDesk> Obj = CurLevel->CreateActor<MiniDesk>();
		const float4 Pos = float4{ -312, -250, -2120 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<MiniDesk> Obj = CurLevel->CreateActor<MiniDesk>();
		const float4 Pos = float4{ 25, -250, -2120 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<MiniDesk> Obj = CurLevel->CreateActor<MiniDesk>();
		const float4 Pos = float4{ 300, -250, -2120 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Conveyor> Obj = CurLevel->CreateActor<Conveyor>();
		const float4 Pos = float4{ -567, -274, -1805 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<TrashCan> Obj = CurLevel->CreateActor<TrashCan>();
		const float4 Pos = float4{ -100 , -314, -3110 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Bench> Obj = CurLevel->CreateActor<Bench>();
		const float4 Pos = float4{ -250, -18, 300 };
		const float4 Rot = float4{ 0, 45, 0 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(Rot, Pos));
	}


	// 난간, 아래쪽부터 순서대로 
	{
		std::shared_ptr<Railing> Obj = CurLevel->CreateActor<Railing>();
		const float4 Pos = float4{ -200, -250, -850 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Railing> Obj = CurLevel->CreateActor<Railing>();
		const float4 Pos = float4{ 180, -250, -850 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Railing> Obj = CurLevel->CreateActor<Railing>();
		const float4 Pos = float4{ 400, 100, 700 };
		const float4 Rot = float4{ 0, 45 , 0 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(Rot, Pos));
	}
	{
		std::shared_ptr<Railing> Obj = CurLevel->CreateActor<Railing>();
		const float4 Pos = float4{ 600, 100, 500 };
		const float4 Rot = float4{ 0, 45 , 0 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(Rot, Pos));
	}
	{
		std::shared_ptr<Railing> Obj = CurLevel->CreateActor<Railing>();
		const float4 Pos = float4{ 2430, 140, 1300 };
		const float4 Rot = float4{ 0, 5 , 0 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(Rot, Pos));
	}
	{
		// 2260, 270 , 1121
		// 휴지통
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.5f, 0.5f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 2220, 270, 1121 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		// 빨래건조대?
		// 1821, 300, 1648
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.5f, 0.5f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 1741, 300, 1548 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	{
		std::shared_ptr<MiniPost> Obj = CurLevel->CreateActor<MiniPost>();
		const float4 Pos = float4{ 1300, 300, 680 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<MiniPost> Obj = CurLevel->CreateActor<MiniPost>();
		const float4 Pos = float4{ 1300, 300, 2080 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		
	}


	// --------------------------------transform wall---------------------------------------------
	{

	}
	// 오피스 초반 책상사이 주변 벽
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.7f, 0.4f, 0.7f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ -327, -274, -1900 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 1.2f, 0.5f, 0.7f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 150, -274, -1900 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.3f, 0.5f, 2.2f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 480, -274, -1900 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	// Office Start 지점 주변 벽 
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 5.1f, 1.0f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 150, -490, -4920 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 5.1f, 1.0f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 2750, -490, -4920 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 1.0f, 0.7f, 1.4f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 4100.0f, -781.0f, -5330.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	// 맵 좌측 일자벽 
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.4f, 1.0f, 8.2f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ -950.0f, -500.0f, -3050.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	// 통과지점 사이 벽 
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 4.8f, 0.5f, 0.6f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 176.0f, -282.0f, -2981.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 2.0f, 0.5f, 0.6f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 2026.0f, -282.0f, -2981.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.45f, 1.0f, 4.2f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 2300.0f, -296.0f, -2390.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 1.1f, 0.5f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 436.0f, -282.0f, -2751.0f };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	// 미니오피스 뒤쪽벽
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 3.5f, 1.0f, 0.4f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 1628, -251, -1631 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	// 스타트 이후 오르막길 왼벽 
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.55f, 2.0f, 2.7f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 1200, -770, -4400 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.7f, 2.0f, 1.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 980, -770, -4600 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.7f, 2.0f, 0.75f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 760, -770, -4650 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	// 스타트 이후 오르막길 오른벽
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.7f, 2.0f, 2.7f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 1710, -700, -4400 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 3.5f, 1.0f, 2.2f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 3000, -270, -4400 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.5f, 1.0f, 5.0f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 3556, -274, -3304 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	// 검사구역 통과 후 언덕라인 벽
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 2.0f, 1.0f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 620, -250, -1330 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 2.0f, 1.0f, 0.5f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ -605, -250, -1250 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, Pos));
	}

	// 초반 언덕 아래 땜빵 wall 
	{
		std::shared_ptr<Transform_Wall> Obj = CurLevel->CreateActor<Transform_Wall>();
		float4 Ratio = float4{ 0.5f, 0.5f, 0.7f };
		Obj->Set_MeshRatio(Ratio);
		const float4 Pos = float4{ 155, -400, -1150 };
		Obj->GetTransform()->SetLocalPosition(Pos);
		Obj->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4{-20, 0, 0}, Pos));
	}

}

void Map_Office::Set_ActiveObject()
{
}
