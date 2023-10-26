#include "PrecompileHeader.h"
#include "Map_Sanctuary.h"

#include "Player.h"

#include "ContentFBXRenderer.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"

#include "SecretTile.h"
#include "FrogFloor.h"

Map_Sanctuary::Map_Sanctuary()
{
}

Map_Sanctuary::~Map_Sanctuary()
{
}

void Map_Sanctuary::OnRotationFloor()
{
	if (nullptr == m_pFrogFloor)
	{
		MsgAssert("FrogFloor가 nullptr 입니다.");
		return;
	}

	m_pFrogFloor->OnRotation();
}

void Map_Sanctuary::OffRotationFloor()
{
	if (nullptr == m_pFrogFloor)
	{
		MsgAssert("FrogFloor가 nullptr 입니다.");
		return;
	}

	m_pFrogFloor->OffRotation();
}

void Map_Sanctuary::NaviRenderSwitch()
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

void Map_Sanctuary::Start()
{
	// 컴포넌트 초기화 
	InitComponent();
	InitKey();

	m_pFrogFloor = GetLevel()->CreateActor<FrogFloor>();
}

void Map_Sanctuary::Update(float _DeltaTime)
{
	KeyUpdate();
}

void Map_Sanctuary::InitKey()
{
	if (false == GameEngineInput::IsKey("test_rot"))
	{
		GameEngineInput::CreateKey("test_rot", '0');
	}
}

void Map_Sanctuary::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("test_rot"))
	{
		if (true == m_pFrogFloor->IsRotation())
		{
			OffRotationFloor();
		}
		else
		{
			OnRotationFloor();
		}
	}
}

void Map_Sanctuary::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Map_Sanctuary.fbx", "ContentMeshDeffered");
	m_pRenderer->GetTransform()->SetLocalRotation(m_MapRot);


	// test 
	auto AllUnit = m_pRenderer->GetAllRenderUnit();
	auto Unit = m_pRenderer->GetUnTexturedUnit();

	m_pNaviRenderer = CreateComponent<ContentFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Map_Sanctuary_Navi.fbx", "ContentMeshDeffered");
	m_pNaviRenderer->GetTransform()->SetLocalRotation(m_NavRot);
	m_pNaviRenderer->Off();

	// float4 UnitScale = m_pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	// float4 scale = m_pRenderer->GetMeshScale();
	// physx::PxVec3 vscale = UnitScale.PhysXVec3Return();

	// 컴포넌트 
	m_pTriangleComp = CreateComponent<PhysXTriangleComponent>();
	m_pTriangleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pTriangleComp->CreatePhysXActors("Map_Sanctuary_Navi.fbx", true);
	m_pTriangleComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(m_NavRot, m_MapPos));
}

void Map_Sanctuary::Create_PhysXComponent()
{
}
