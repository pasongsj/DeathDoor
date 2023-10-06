#include "PrecompileHeader.h"
#include "FrogFloor.h"

#include "SecretTile.h"

#include "ContentFBXRenderer.h"
#include "PhysXBoxComponent.h"

#include "FireObject.h"

FrogFloor::FrogFloor()
{
}

FrogFloor::~FrogFloor()
{
}

void FrogFloor::Start()
{
	InitComponent();
}

void FrogFloor::Update(float _DeltaTime)
{
}

void FrogFloor::InitComponent()
{
	GetTransform()->SetLocalPosition(float4{ -3621, -197, 3700 });

	m_pHingeRenderer = CreateComponent<ContentFBXRenderer>();
	m_pHingeRenderer->SetFBXMesh("Hinge.fbx", "ContentMeshDeffered");
	//m_pHingeRenderer->GetTransform()->SetLocalRotation(float4{ 0 , -40, 0 });
	//m_pHingeRenderer->GetTransform()->SetLocalPosition(float4{ -3621, -197, 3700 });

	{
		std::shared_ptr<FireObject> FireObj = GetLevel()->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(float4{ 200, 200 , 200 });
		FireObj->GetTransform()->SetLocalPosition(float4{ -3400, 167, 2420 });
	}
	{
		std::shared_ptr<FireObject> FireObj = GetLevel()->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(float4{ 200, 200 , 200 });
		FireObj->GetTransform()->SetLocalPosition(float4{ -4770, 167, 4040 });
	}
	{
		std::shared_ptr<FireObject> FireObj = GetLevel()->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(float4{ 200, 200 , 200 });
		FireObj->GetTransform()->SetLocalPosition(float4{ -3150, 167, 5370 });
	}
	{
		std::shared_ptr<FireObject> FireObj = GetLevel()->CreateActor<FireObject>();
		FireObj->GetTransform()->SetLocalScale(float4{ 200, 200 , 200 });
		FireObj->GetTransform()->SetLocalPosition(float4{ -1790, 167, 3760 });
	}
	
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

	// 돌면서 5x5 타일 깔아 
	for (size_t i = 0; i < m_Width; ++i)
	{
		for (size_t j = 0; j < m_Height; ++j)
		{
			// 타일만들고
			std::shared_ptr<SecretTile> NewTile = CurLevel->CreateActor<SecretTile>();
			NewTile->GetTransform()->SetParent(GetTransform());

			// 위치세팅하고 
			NewTile->GetTransform()->SetLocalPosition(TileStartPos + MoveXPos + MoveZPos);

			// 벡터에 넣어
			m_vTiles.push_back(NewTile);

			MoveXPos += float4{ PosX , 0,  0 };
		}

		MoveXPos = float4::ZERONULL;
		MoveZPos -= float4{ 0 , 0 , PosZ };
	}

	GetTransform()->SetLocalRotation(float4{ 0 , -40, 0 });
}
