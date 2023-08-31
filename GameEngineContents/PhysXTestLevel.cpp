#include "PreCompileHeader.h"
#include "PhysXTestLevel.h"
#include "PhysXTestActor.h"
#include "PhysXTestPlane.h"
#include "Player.h"

PhysXTestLevel::PhysXTestLevel() 
{
}

PhysXTestLevel::~PhysXTestLevel() 
{
}

void PhysXTestLevel::Start()
{
	SetLevelType(PacketLevelType::PhysXTestLevel);
}

void PhysXTestLevel::LevelChangeStart()
{
	PhysXLevel::LevelChangeStart();
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.f,0.f,0.f });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,1000, .0f });


	{
		std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	}

	CreateActor<PhysXTestActor>();
	//CreateActor<PhysXTestPlane>();
	CreateActor<Player>();
	
	std::shared_ptr<PhysXTestPlane> pWallPlane = CreateActor<PhysXTestPlane>();
}

void PhysXTestLevel::LevelChangeEnd()
{
	PhysXLevel::LevelChangeEnd();
	AllActorDestroy();
}

void PhysXTestLevel::Update(float _DeltaTime)
{
	PhysXLevel::Update(_DeltaTime);
}
