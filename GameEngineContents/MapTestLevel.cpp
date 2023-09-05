#include "PrecompileHeader.h"
#include "MapTestLevel.h"

#include "Player.h"
#include "Map_Office.h"
#include "Map_Emptyplain.h"
#include "PhysXCapsuleComponent.h"



MapTestLevel::MapTestLevel()
{
}

MapTestLevel::~MapTestLevel()
{
}

void MapTestLevel::Start()
{
	SetLevelType(PacketLevelType::PhysXTestLevel);
	CreateScene();
	SetTestLevelType(TestMapType::BigCrow_Floor);
}

void MapTestLevel::Update(float _DeltaTime)
{
	PhysXLevel::Update(_DeltaTime);
}

void MapTestLevel::LevelChangeStart()
{
	PhysXLevel::LevelChangeStart();
	
	InitTestLevel();
	
	CreateActor<GameEngineLight>();
}

void MapTestLevel::LevelChangeEnd()
{
	PhysXLevel::LevelChangeEnd();
	AllActorDestroy();
}

void MapTestLevel::InitTestLevel()
{
	if (TestMapType::None == m_Type)
	{
		MsgAssert("테스트 레벨 타입을 세팅하지 않았습니다.");
		return;
	}
	
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	switch (m_Type)
	{
	case TestMapType::Office:
	{
		GetMainCamera()->GetTransform()->SetLocalRotation({ 35.0f, 0.0f, 0.0f });
		GetMainCamera()->GetTransform()->SetLocalPosition(float4{ 2800 , 230 , -6300 });

		CreateActor<Map_Office>();
		std::shared_ptr<Player> Obj = CreateActor<Player>();
		if (nullptr != Obj)
		{
			Obj->GetPhysXComponent()->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, float4{ 2610 , -574 , -5347 }));
		}
	}
	case TestMapType::BigCrow_Floor:
	{
		GetMainCamera()->GetTransform()->SetLocalPosition(float4{ 0, 700, -2500 });

		std::shared_ptr<Map_Emptyplain> NewMap = CreateActor<Map_Emptyplain>(); 
		CreateActor<Player>();
		
	}
		break;
	}
}
