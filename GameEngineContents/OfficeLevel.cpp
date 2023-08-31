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
	SetLevelType(PacketLevelType::OfficeLevel);
}

void OfficeLevel::Update(float _DeltaTime)
{
	PhysXLevel::Update(_DeltaTime);
}

void OfficeLevel::LevelChangeStart()
{
	PhysXLevel::LevelChangeStart();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ -415, 500, 100 });

	std::shared_ptr<Map_Office> Obj = CreateActor<Map_Office>();
	
	
}

void OfficeLevel::LevelChangeEnd()
{
	PhysXLevel::LevelChangeEnd();
	AllActorDestroy();
}
