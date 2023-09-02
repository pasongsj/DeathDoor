#include "PrecompileHeader.h"
#include "OfficeLevel.h"

#include "Map_PhysXActor.h"
#include "Map_Office.h"

OfficeLevel::OfficeLevel()
{
}

OfficeLevel::~OfficeLevel()
{
}

void OfficeLevel::Start()
{
	CreateScene();
	SetLevelType(PacketLevelType::OfficeLevel);
}

void OfficeLevel::Update(float _DeltaTime)
{
}

void OfficeLevel::LevelChangeStart()
{

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ -415, 500, 100 });

	CreateActor<GameEngineLight>();
	CreateActor<Map_Office>();
	
	
}

void OfficeLevel::LevelChangeEnd()
{
	AllActorDestroy();
}
