#include "PrecompileHeader.h"
#include "MapTestLevel.h"

#include "Player.h"
#include "Map_Office.h"
#include "Map_Emptyplain.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXBoxComponent.h"


#include "EnemyBat.h"
#include "EnemyFirePlant.h"
#include "EnemyMage.h"
#include "EnemyGrunt.h"
#include "EnemyBrute.h"
#include "EnemyGhoul.h"
#include "EnemyBruteGold.h"
#include "MonsterAnimationTest.h"

//test 
#include "SecretTile.h"
#include "Ladder.h"
#include "Crate.h"
#include "Frog_Lever.h"
#include "PlayerAttackMagic.h"


#include "PlayerAttackTrail.h"



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
}

void MapTestLevel::LevelChangeStart()
{
	CreateScene();
	SetTestLevelType(TestMapType::BigCrow_Floor);

	InitTestLevel();
	
	CreateActor<GameEngineLight>();

	CreateUI();
	SetPostPrecessEffect();
}

void MapTestLevel::LevelChangeEnd()
{
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
		break;
	case TestMapType::BigCrow_Floor:
	{
		GetMainCamera()->GetTransform()->SetLocalPosition(float4{ 0, 700, -2500 });
		std::shared_ptr<SecretTile> NewTile = CreateActor<SecretTile>();
		NewTile->GetTransform()->SetLocalPosition(float4{ -400, 100 , 0 });

		std::shared_ptr<Crate> NewCrate = GetLevel()->CreateActor<Crate>();
		NewCrate->GetTransform()->SetLocalPosition(float4{ 400, 0 , 0 });

		std::shared_ptr<Ladder> NewLadder = CreateActor<Ladder>();
		NewLadder->GetTransform()->SetLocalRotation(float4{ 0, 90,  0 });
		NewLadder->GetTransform()->SetLocalPosition(float4{ 800, 0 , 0 });
		

		// std::shared_ptr<Frog_Lever> Lever = CreateActor<Frog_Lever>();

		std::shared_ptr<Map_Emptyplain> NewMap = CreateActor<Map_Emptyplain>();
		std::shared_ptr<Player> Obj = CreateActor<Player>();
		if (nullptr != Obj)
		{
			Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ 1000.0f , 1000.0f , 0.0f });
		}
		
		CreateActor<EnemyFirePlant>();
		//CreateActor<PlayerAttMagic>();
		
		break;
	}
	}


}
