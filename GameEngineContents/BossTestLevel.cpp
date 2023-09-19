#include "PreCompileHeader.h"

#include "BossLevelTestObject.h"
#include "Boss_OldCrow.h"
#include "Player.h"

#include "PhysXTestPlane.h"
#include "BossTestLevel.h"



BossTestLevel::BossTestLevel() 
{
}

BossTestLevel::~BossTestLevel() 
{
}

void BossTestLevel::Start()
{	
	CreateActor<GameEngineLight>();
}

void BossTestLevel::Update(float _DeltaTime)
{
	float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	Pos += {0, 2500, 0};

	if (!GetMainCamera()->IsFreeCamera())
	{
		GetMainCamera()->GetTransform()->SetWorldPosition(Pos);
	}
}


void BossTestLevel::LevelChangeStart()
{
	CreateScene();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0 });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 500.0f, 0.0f });

	//std::shared_ptr<BossLevelTestObject> TestObject = CreateActor<BossLevelTestObject>();
	//TestObject->GetTransform()->SetLocalScale({ 100, 100, 100 });
	//TestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });

	std::shared_ptr<PhysXTestPlane> TestPlaneObject = CreateActor<PhysXTestPlane>();
	TestPlaneObject->GetTransform()->AddLocalScale({ 4, 4, 4 });

	std::shared_ptr<Player> TestPlayer = CreateActor<Player>();
	TestPlayer->GetTransform()->SetWorldPosition({ 0, -100, 0 });

	std::shared_ptr<Boss_OldCrow> BossTestObject = CreateActor<Boss_OldCrow>();
	//BossTestObject->GetTransform()->SetWorldPosition({-1000, 0, -1000});
	//BossTestObject->GetTransform()->SetWorldRotation({ 0, 180, 0 });
	//BossTestObject->Init();
	//BossTestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });
}

void BossTestLevel::LevelChangeEnd()
{

}
