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
#include "MonsterAnimationTest.h"

//test 
#include "SecretTile.h"
#include "Ladder.h"
#include "Crate.h"
#include "CapsulTestActor.h"



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
}

void MapTestLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void MapTestLevel::InitTestLevel()
{
	if (TestMapType::None == m_Type)
	{
		MsgAssert("�׽�Ʈ ���� Ÿ���� �������� �ʾҽ��ϴ�.");
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
		CreateActor<SecretTile>();
		GetLevel()->CreateActor<Crate>();
		std::shared_ptr<Ladder> NewLadder = CreateActor<Ladder>();
		NewLadder->GetTransform()->SetLocalRotation(float4{ 0, 90 , 0 });
		NewLadder->GetTransform()->SetWorldPosition(float4{ 500, 50, -400 });


		NewLadder->GetPhysXComponent()->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4{ 0, 90 , 0 }, float4{ 500, 50, -400 }));

		std::shared_ptr<Map_Emptyplain> NewMap = CreateActor<Map_Emptyplain>();
		std::shared_ptr<Player> Obj = CreateActor<Player>();
		if (nullptr != Obj)
		{
			Obj->GetPhysXComponent()->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, float4{ 1000.0f , -0.0f , -0.0f }));
		}
		//CreateActor<MonsterAnimationTest>();
		//CreateActor<Player>();
		CreateActor<EnemyFirePlant>();
		CreateActor<CapsulTestActor>();
		//std::shared_ptr<EnemyFirePlant> monster =  CreateActor<EnemyFirePlant>();
		//if (nullptr != monster)
		//{
		//	monster->GetPhysXComponent()->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, float4{ 0.0f , 100.0f , -0.0f }));
		//}

		//test 
		
		break;
	}
	}


}
