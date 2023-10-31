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

const float4 Map_Sanctuary::GetTilePos(const int _Y, const int _X)
{
	std::vector<std::vector<std::shared_ptr<SecretTile>>> Tiles = m_pFrogFloor->GetTiles();
	if (_X < 0 || _X >= 5)
	{
		MsgAssert("X 인덱스 값이 잘못되었습니다.");
	}

	if (_Y < 0 || _Y >= 5)
	{
		MsgAssert("Y 인덱스 값이 잘못되었습니다.");
	}

	const float4 TilePos = Tiles[_Y][_X]->GetTransform()->GetWorldPosition();


	return TilePos;
}

const float4 Map_Sanctuary::GetTileIndex(const float4& _Pos)
{
	// 타일 배열 받아오고
	std::vector<std::vector<std::shared_ptr<SecretTile>>> Tiles = m_pFrogFloor->GetTiles();
	if (true == Tiles.empty())
	{
		MsgAssert("타일 버퍼가 비어있습니다.");
	}

	float4 TilePos = Tiles[0][0]->GetTransform()->GetWorldPosition();
	float4 TileScale = Tiles[0][0]->GetRender()->GetMeshScale();
	float TileSize = Tiles[0][0]->GetTileSize();

	float4 Start = TilePos - float4{ 0, 0, -TileSize };
	
	float TempX = (_Pos.x - Start.x);
	float TempZ = (_Pos.z - Start.z);
	
	int X = static_cast<int>((TempX / TileSize + -TempZ / TileSize) / 2.0f);
	int Z = static_cast<int>((-TempZ / TileSize - (TempX / TileSize)) / 2.0f );

	float4 TileIndex = float4{ static_cast<float>(X),static_cast<float>(Z), 0 };

	return TileIndex;
}

void Map_Sanctuary::DestroyTile(const int _Y, const int _X)
{
	m_pFrogFloor->DestroyTile(_Y, _X);
}

bool Map_Sanctuary::IsTile(const int _Y, const int _X)
{
	return m_pFrogFloor->IsTile(_Y, _X);
}

void Map_Sanctuary::ResetTile()
{
	m_pFrogFloor->ResetTile();
}

void Map_Sanctuary::ShakeTile(const int _Y, const int _X, float _ShakeTime)
{
	m_pFrogFloor->ShakeTile(_Y, _X, _ShakeTime);
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
	m_pRenderer->SetFBXMesh("Map_Sanctuary_Blender.fbx", "ContentMeshDeffered");
	m_pRenderer->GetTransform()->SetLocalRotation(m_MapRot);


	// test 
	auto AllUnit = m_pRenderer->GetAllRenderUnit();
	AllUnit[0][0]->Off();
	AllUnit[1][0]->Off();
	AllUnit[2][0]->Off();
	AllUnit[3][0]->Off();
	AllUnit[4][0]->Off();
	auto Unit = m_pRenderer->GetUnTexturedUnit();

	m_pNaviRenderer = CreateComponent<ContentFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Map_Sanctuary_Navi_Blender.fbx", "ContentMeshDeffered");
	m_pNaviRenderer->GetTransform()->SetLocalRotation(m_NavRot);
	m_pNaviRenderer->Off();

	// float4 UnitScale = m_pRenderer->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	// float4 scale = m_pRenderer->GetMeshScale();
	// physx::PxVec3 vscale = UnitScale.PhysXVec3Return();

	// 컴포넌트 
	m_pTriangleComp = CreateComponent<PhysXTriangleComponent>();
	m_pTriangleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pTriangleComp->CreatePhysXActors("Map_Sanctuary_Navi_Blender.fbx", true);
	m_pTriangleComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(m_NavRot, m_MapPos));
}

void Map_Sanctuary::Create_PhysXComponent()
{
}
