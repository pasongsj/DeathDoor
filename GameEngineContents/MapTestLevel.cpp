#include "PrecompileHeader.h"
#include "MapTestLevel.h"

#include "TestMap.h"
#include "Player.h"

MapTestLevel::MapTestLevel()
{
}

MapTestLevel::~MapTestLevel()
{
}

void MapTestLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 300, 0, -900.0f });

	CreateActor<TestMap>();
}

void MapTestLevel::Update(float _DeltaTime)
{
}

void MapTestLevel::LevelChangeStart()
{
}

void MapTestLevel::LevelChangeEnd()
{
}
