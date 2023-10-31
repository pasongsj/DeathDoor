#include "PrecompileHeader.h"
#include "TileManager.h"

#include "SecretTile.h"

#include "ContentFBXRenderer.h"
#include "PhysXBoxComponent.h"

#include "FireObject.h"
#include "RuinsWall.h"
#include "Ladder.h"


TileManager* TileManager::MainManager = nullptr;

TileManager::TileManager()
{
	MainManager = this;
}

TileManager::~TileManager()
{
}

void TileManager::Start()
{
	InitComponent();
}

void TileManager::Update(float _DeltaTime)
{
	RotationUpdate(_DeltaTime);
}

const float4 TileManager::GetTilePos(const int _Y, const int _X)
{
	if (_X < 0 || _X >= 5)
	{
		MsgAssert("X 인덱스 값이 잘못되었습니다.");
	}

	if (_Y < 0 || _Y >= 5)
	{
		MsgAssert("Y 인덱스 값이 잘못되었습니다.");
	}

	const float4 TilePos = m_vTiles[_Y][_X]->GetTransform()->GetWorldPosition();

	return TilePos;
}

const float4 TileManager::GetTileIndex(const float4& _Pos)
{
	if (true == m_vTiles.empty())
	{
		MsgAssert("타일 버퍼가 비어있습니다.");
	}

	float4 TilePos = m_vTiles[0][0]->GetTransform()->GetWorldPosition();
	float4 TileScale = m_vTiles[0][0]->GetRender()->GetMeshScale();
	float TileSize = m_vTiles[0][0]->GetTileSize();

	float4 Start = TilePos - float4{ 0, 0, -TileSize };

	float TempX = (_Pos.x - Start.x);
	float TempZ = (_Pos.z - Start.z);

	int X = static_cast<int>((TempX / TileSize + -TempZ / TileSize) / 2.0f);
	int Z = static_cast<int>((-TempZ / TileSize - (TempX / TileSize)) / 2.0f);

	float4 TileIndex = float4{ static_cast<float>(X),static_cast<float>(Z), 0 };

	return TileIndex;
}

void TileManager::DestroyTile(const int _Y, const int _X)
{
	if (_Y == -1 && _X == -1)
	{
		return;
	}


	if (true == m_vTiles[_Y][_X]->IsActive())
	{
		m_vTiles[_Y][_X]->InActive();
		return;
	}

	if (false == m_vTiles[_Y][_X]->IsActive())
	{
		MsgAssert("이미 사라져 있는 타일을 파괴하려고 했습니다.");
		return;
	}
}

bool TileManager::IsTile(const int _Y, const int _X)
{
	if (true == m_vTiles.empty())
	{
		MsgAssert("타일 버퍼가 비어있습니다.");
	}
	if (_Y < 0 || _Y >= m_vTiles.size() || _X < 0 || _X >= m_vTiles[_Y].size())
	{
		return false;
	}
	if (true == m_vTiles[_Y][_X]->IsActive())
	{
		return true;
	}

	return false;
}

void TileManager::ResetTile()
{
	if (true == m_vTiles.empty())
	{
		MsgAssert("타일 버퍼가 비어있습니다.");
		return;
	}

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (false == m_vTiles[i][j]->IsActive())
			{
				m_vTiles[i][j]->Active();
			}
		}
	}
}

void TileManager::ShakeTile(const int _Y, const int _X, float _ShakeTime)
{
	if (_Y < 0 || _Y >= m_vTiles.size() || _X < 0 || _X >= m_vTiles[_Y].size())
	{
		MsgAssert("인덱스 범위를 초과했습니다.");
		return;
	}

	m_vTiles[_Y][_X]->OnShake(_ShakeTime);
}

void TileManager::RotationUpdate(float _DeltaTime)
{
	float4 Rot = m_pPivotTile.lock()->GetTransform()->GetLocalRotation();

	if (true == m_bRotation)
	{
		if (Rot.z >= -15.0f)
		{
			m_pPivotTile.lock()->GetTransform()->AddLocalRotation(float4{ 0, 0, -0.35f });
		}
	}

	else if (false == m_bRotation)
	{
		if (Rot.z < 0.0f)
		{
			m_pPivotTile.lock()->GetTransform()->AddLocalRotation(float4{ 0, 0, 0.2f });
		}
	}
}



void TileManager::InitComponent()
{
	GetTransform()->SetLocalPosition(m_f4FloorPos);

	// 테두리 렌더러 생성
	m_pHingeRenderer = CreateComponent<ContentFBXRenderer>();
	m_pHingeRenderer->SetFBXMesh("Hinge.fbx", "ContentMeshDeffered");

	m_pWiresRenderer = CreateComponent<ContentFBXRenderer>();
	m_pWiresRenderer->SetFBXMesh("Wires.fbx", "ContentMeshDeffered");
	m_pWiresRenderer->GetTransform()->AddLocalPosition(float4{ 0, -30, 0 });

	Create_TileObject();
	Create_FireObject();

	// 회전 
	GetTransform()->SetLocalRotation(float4{ 0 , 45 , 0 });
	
	Create_WallObject();

	std::shared_ptr<Ladder> Obj = GetLevel()->CreateActor<Ladder>();
	Obj->GetTransform()->SetLocalRotation(float4{ 0, 45, 0 });
	Obj->GetTransform()->SetLocalPosition(float4{ -4880,  -40 , 4947 });

	for (size_t i = 0; i < m_vFireObjects.size(); i++)
	{
		m_vFireObjects[i]->GetTransform()->SetParent(GetTransform());
	}


	m_pPivotTile = GetLevel()->CreateActor<SecretTile>();
	m_pPivotTile.lock()->GetRender()->Off();
	m_pPivotTile.lock()->GetTransform()->SetWorldPosition(float4{-3213, -350, 3215});
	m_pPivotTile.lock()->GetTransform()->SetLocalRotation(float4{0, 45, 0});
	m_pPivotTile.lock()->GetPhysXComponent()->Death();

	GetTransform()->SetParent(m_pPivotTile.lock()->GetTransform());
}

void TileManager::Create_FireObject()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}
	
	m_vFireObjects.reserve(4);

	{
		// 12 
		std::shared_ptr<FireObject> FireObj = CurLevel->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(m_FireObjScale);
		FireObj->GetTransform()->SetLocalPosition(float4{ -3615, 197, 5115 });
		FireObj->SetRotation({ 0.0f, -135.0f, 0.0f });
		m_vFireObjects.push_back(FireObj);
	}
	{
		// 3
		std::shared_ptr<FireObject> FireObj = CurLevel->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(m_FireObjScale);
		FireObj->GetTransform()->SetLocalPosition(float4{ -2140, 197, 3635 });
		FireObj->SetRotation({ 0.0f, -135.0f, 0.0f });
		m_vFireObjects.push_back(FireObj);
	}
	{
		// 6
		std::shared_ptr<FireObject> FireObj = CurLevel->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(m_FireObjScale);
		FireObj->GetTransform()->SetLocalPosition(float4{ -3630, 197, 2151 });
		FireObj->SetRotation({ 0.0f, -135.0f, 0.0f });
		m_vFireObjects.push_back(FireObj);
	}
	{
		// 9
		std::shared_ptr<FireObject> FireObj = CurLevel->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(m_FireObjScale);
		FireObj->GetTransform()->SetLocalPosition(float4{ -5110 , 197 , 3619 });
		FireObj->SetRotation({ 0.0f, -135.0f, 0.0f });
		m_vFireObjects.push_back(FireObj);
	}
}

void TileManager::Create_TileObject()
{
	float4 TileStartPos = m_TileInitPos;

	float PosX = m_fTileMovePos;
	float PosZ = m_fTileMovePos;

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}

	// 초기위치 
	float4 StartPos = m_TileInitPos;
	float4 MoveXPos = float4::ZERONULL;
	float4 MoveZPos = float4::ZERONULL;

	m_vTiles.resize(5);


	// 돌면서 5x5 타일 깔아 
	for (size_t i = 0; i < m_Height; ++i)
	{
		m_vTiles[i].resize(5);
		float4 MovePos = {};

		for (size_t j = 0; j < m_Width; ++j)
		{
			// 타일만들고
			std::shared_ptr<SecretTile> NewTile = CurLevel->CreateActor<SecretTile>();
			NewTile->GetTransform()->SetParent(GetTransform());

			MovePos = NewTile->GetRender()->GetMeshScale();

			// 위치세팅하고 
			NewTile->GetTransform()->SetLocalPosition(TileStartPos + MoveXPos + MoveZPos);
			NewTile->GetTransform()->SetLocalPosition(NewTile->GetTransform()->GetLocalPosition() + float4 { 0, -40, 0 });
			NewTile->SetTileIndex(static_cast<int>(i),static_cast<int>(j));

			// 벡터에 넣어
			m_vTiles[i][j] = NewTile;

			MoveXPos += float4{ MovePos.x, 0, 0 };
		}

		MoveXPos = float4::ZERONULL;
		MoveZPos -= float4{ 0, 0, MovePos.z };
	}
}

void TileManager::Create_WallObject()
{
	m_vWalls.reserve(4);

	GameEngineLevel* CurLevel = GetLevel();
	

	float4 FloorPos = GetTransform()->GetLocalPosition();
	float4 re = float4{ -4376, -322, 2889 } - FloorPos;
	// z : - 350
	// x : - 350 
	{
		std::shared_ptr<RuinsWall> Obj = CurLevel->CreateActor<RuinsWall>();
		Obj->GetTransform()->SetLocalPosition(FloorPos + float4 { -505, -127, -1061 });
		Obj->GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });
		Obj->GetTransform()->SetParent(GetTransform());
		m_vWalls.push_back(Obj);
	}
	{
		std::shared_ptr<RuinsWall> Obj = CurLevel->CreateActor<RuinsWall>();
		Obj->GetTransform()->SetLocalPosition(FloorPos + float4 { 950 , -127, 400 });
		Obj->GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });
		Obj->GetTransform()->SetParent(GetTransform());
		m_vWalls.push_back(Obj);
	}
	{
		std::shared_ptr<RuinsWall> Obj = CurLevel->CreateActor<RuinsWall>();
		Obj->GetTransform()->SetLocalPosition(FloorPos + float4 { 980, -127, -1080});
		Obj->GetTransform()->SetLocalRotation(float4{ 0, 45, 0 });
		Obj->GetTransform()->SetParent(GetTransform());
		m_vWalls.push_back(Obj);
	}
	{
		std::shared_ptr<RuinsWall> Obj = CurLevel->CreateActor<RuinsWall>();
		Obj->GetTransform()->SetLocalPosition(FloorPos + float4 { -550 , -127, 400 });
		Obj->GetTransform()->SetLocalRotation(float4{ 0, 45, 0 });
		Obj->GetTransform()->SetParent(GetTransform());
		m_vWalls.push_back(Obj);
	}
}

