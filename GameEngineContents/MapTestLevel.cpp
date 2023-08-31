#include "PrecompileHeader.h"
#include "MapTestLevel.h"

#include "TestMap.h"
#include "Player.h"
#include "Map_PhysXActor.h"


MapTestLevel::MapTestLevel()
{
}

MapTestLevel::~MapTestLevel()
{
}

void MapTestLevel::Start()
{
	SetLevelType(PacketLevelType::PhysXTestLevel);
}

void MapTestLevel::Update(float _DeltaTime)
{
	PhysXLevel::Update(_DeltaTime);
}

void MapTestLevel::LevelChangeStart()
{
	PhysXLevel::LevelChangeStart();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 300, 0, -900.0f });

	CreateActor<GameEngineLight>();
	CreateActor<Map_PhysXActor>();
	CreateActor<TestMap>();
}

void MapTestLevel::LevelChangeEnd()
{
	PhysXLevel::LevelChangeEnd();
	AllActorDestroy();
}
