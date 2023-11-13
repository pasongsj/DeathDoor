#include "PreCompileHeader.h"

#include "BossLevelTestObject.h"
#include "Boss_OldCrow.h"
#include "Player.h"
#include "Map_Emptyplain.h"

#include "EnemyBrute.h"
#include "EnemyBruteGold.h"
#include "EnemyFirePlant.h"
#include "EnemyGhoul.h"
#include "EnemyGhoulBig.h"
#include "EnemyGrunt.h"
#include "EnemyJumper.h"
#include "EnemyMage.h"

#include "PhysXTestPlane.h"
#include "BossTestLevel.h"
#include "PhysXControllerComponent.h"



BossTestLevel::BossTestLevel() 
{
}

BossTestLevel::~BossTestLevel() 
{
}

void BossTestLevel::Start()
{	
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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 300.0f, 0.0f });

	CreateActor<GameEngineLight>();

	//std::shared_ptr<BossLevelTestObject> TestObject = CreateActor<BossLevelTestObject>();
	//TestObject->GetTransform()->SetLocalScale({ 100, 100, 100 });
	//TestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });

	std::shared_ptr<Map_Emptyplain> NewMap = CreateActor<Map_Emptyplain>();

	std::shared_ptr<Player> TestPlayer = CreateActor<Player>();

	if (nullptr != TestPlayer)
	{
		TestPlayer->GetPhysXComponent()->SetWorldPosWithParent(float4::ZERO, float4::ZERO);
	}

	std::shared_ptr<EnemyMage> BossTestObject = CreateActor<EnemyMage>();

	if (nullptr != BossTestObject)
	{
		BossTestObject->GetPhysXComponent()->SetWorldPosWithParent(float4{ 0, 0, -2000 },float4{0, 90, 0});
	}

	//BossTestObject->GetTransform()->SetWorldPosition({-1000, 0, -1000});
	//BossTestObject->GetTransform()->SetWorldRotation({ 0, 180, 0 });
	//BossTestObject->Init();
	//BossTestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });


	LevelInit({ 800, 450, 800, 450 });
}

void BossTestLevel::LevelChangeEnd()
{
	AllActorDestroy();
}
