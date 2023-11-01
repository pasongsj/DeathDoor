#include "PrecompileHeader.h"
#include "FortressLevel.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"

#include "Player.h"
#include "Map_Fortress.h"
#include "CullingManager.h"
#include "WaterBox.h"
#include "BossFrog.h"


// enemy 
#include "EnemyBrute.h"
#include "EnemyBruteGold.h"
#include "EnemyFirePlant.h"
#include "EnemyGhoul.h"
#include "EnemyGhoulBig.h"
#include "EnemyGrunt.h"
#include "EnemyJumper.h"
#include "EnemyMage.h"

// field obj
#include "Ladder.h"
#include "Frog_Lever.h"
#include "Frog_Septre.h"
#include "ShortCutDoor.h"
#include "Mushroom.h"

FortressLevel::FortressLevel()
{
}

FortressLevel::~FortressLevel()
{
}

void FortressLevel::Start()
{
	SetContentLevelType(ContentLevelType::FortressLevel);
	InitKey();
}

void FortressLevel::Update(float _DeltaTime)
{
	KeyUpdate(_DeltaTime);


	float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();

	// test 
	if (false == GetMainCamera()->IsFreeCamera())
	{
		float4 nextPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		nextPos.y += 1000.0f;
		nextPos.z -= 1000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad);
		GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
	}
}

void FortressLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch_Fortress"))
	{
		GameEngineInput::CreateKey("NaviMesh_Switch_Fortress", 'M');
		GameEngineInput::CreateKey("Fortress_Trigger_Switch", 'T');
	}
}

void FortressLevel::KeyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
		if (nullptr != m_pMap)
		{
			m_pMap->NaviRenderSwitch();
		}
	}

	if (true == GameEngineInput::IsDown("Fortress_Trigger_Switch"))
	{
		if (nullptr != m_pMap)
		{
			m_pMap->TriggerSwitch();
		}
	}
}

void FortressLevel::LevelChangeStart()
{
	CreateScene();

	LevelInit({ 800, 450, 800, 450 });

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	Light->GetTransform()->SetLocalRotation(float4{ 45, 90 , 0 });

	m_pMap = CreateActor<Map_Fortress>();

	std::shared_ptr<Player> Obj = CreateActor<Player>();
	float4 Pos = Obj->GetTransform()->GetWorldPosition();
	Set_PlayerStartPos();

	Create_Manager();

	std::shared_ptr<GameEngineActor> Actor = CreateActor<GameEngineActor>();
	std::shared_ptr<WaterBox> Box = Actor->CreateComponent<WaterBox>();

	Box->SetWaterPosition({ -5000, -120 ,4500 });
	Box->GetTransform()->SetLocalScale({ 15000 , 1 , 15000 });
	Box->GetTransform()->SetLocalRotation({ 0 , 45.0f , 0 });


	Create_FieldEnemy();
	Create_FieldObject();
}

void FortressLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void FortressLevel::Set_PlayerStartPos()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("Player 가 nullptr 입니다.");
		return;
	}

	std::shared_ptr<PhysXControllerComponent> Comp = Player::MainPlayer->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}

	Comp->SetWorldPosWithParent(m_StartPos,float4::ZERO);
}

void FortressLevel::Create_Manager()
{
	m_pCullingManager = CreateActor<CullingManager>();
}

void FortressLevel::Create_FieldEnemy()
{
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1656, -6, 514 });
	}
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -972, -6, 1706 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -3054, -6, 3439 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -3388, -6, 2988 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -3862, -6, 3031 });
	}
	{
		std::shared_ptr<EnemyJumper> Monster = CreateActor<EnemyJumper>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1400, 146, 5013 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ 337, 139, 4000 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ 715, 140, 4647 });
	}
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -55, 140, 4234 });
	}
	{
		std::shared_ptr<EnemyMage> Monster = CreateActor<EnemyMage>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1585, 146, 6556 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ 1082, 595, 6392 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -237, 595, 6737 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -182, 595, 7702 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1452, 595, 7571 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -2851, 593, 9373 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -2308, 593, 9914 });
	}
	{
		std::shared_ptr<EnemyJumper> Monster = CreateActor<EnemyJumper>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1482, 593, 9087 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -2255, -6, 7951 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ - 2368, -6, 8466 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -4515, -53, 7123 });
	}
	{
		std::shared_ptr<EnemyJumper> Monster = CreateActor<EnemyJumper>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -3006, -6, 5802 });
	}
	{
		std::shared_ptr<EnemyGhoulBig> Monster = CreateActor<EnemyGhoulBig>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -4768, -6, 4968 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -5131, -6, 4671 });
	}
	{
		std::shared_ptr<EnemyJumper> Monster = CreateActor<EnemyJumper>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -5758, -6, 2642 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -6374, -6, 3598 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -5071, -6, 2146 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -8308, -6, 2334 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -8421, -6, 1527 });
	}
	{
		std::shared_ptr<EnemyMage> Monster = CreateActor<EnemyMage>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -9355, -6, 2211 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -9873, -6, 2915 });
	}
	{
		std::shared_ptr<EnemyGrunt> Monster = CreateActor<EnemyGrunt>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -9923, -6, 3578 });
	}
	{
		std::shared_ptr<EnemyGhoulBig> Monster = CreateActor<EnemyGhoulBig>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -9352, -6, 3705 });
	}
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -9237, -6, 4168 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -11177, 40, 5777 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -10732, 46, 6292 });
	}
	{
		std::shared_ptr<EnemyBruteGold> Monster = CreateActor<EnemyBruteGold>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -10908, 26, 6030 });
	}
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -12380, 46, 6936 });
	}
	{
		std::shared_ptr<EnemyGhoul> Monster = CreateActor<EnemyGhoul>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -12658, 46, 7780 });
	}
	{
		std::shared_ptr<EnemyFirePlant> Monster = CreateActor<EnemyFirePlant>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -11822, -6, 6028 });
	}
	{
		std::shared_ptr<EnemyBruteGold> Monster = CreateActor<EnemyBruteGold>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -12816, 46, 5620 });
	}
	{
		std::shared_ptr<EnemyMage> Monster = CreateActor<EnemyMage>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -14031, 46, 6810 });
	}
	{
		std::shared_ptr<EnemyBrute> Monster = CreateActor<EnemyBrute>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -14128, 46, 8229 });
	}
	{
		std::shared_ptr<EnemyMage> Monster = CreateActor<EnemyMage>();
		Monster->GetPhysXComponent()->SetWorldPosWithParent(float4{ -14104, 46, 8449 });
	}
}

void FortressLevel::Create_FieldObject()
{
	{
		std::shared_ptr<Ladder> Obj = CreateActor<Ladder>();
		Obj->GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -2310, -160, 750 });
	}

	{
		// 큰대문과 세트인 레버
		std::shared_ptr<Frog_Lever> Obj = CreateActor<Frog_Lever>();
		Obj->GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -2750, 320, 1750 });

		// 마지막에 대문 만들어
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ 665, -6, 49 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -733, -6, -140 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -838, -6, 2030 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -1893, -6, 873 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -178, 146, 6317 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -846, 146, 5913 });
	}
	{
		std::shared_ptr<Mushroom> Obj = CreateActor<Mushroom>();
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ -977, 146, 6962 });
	}
	{
		// set 
		std::shared_ptr<Frog_Lever> Obj = CreateActor<Frog_Lever>();
		Obj->GetTransform()->SetLocalRotation(float4{ 0, 45, 0 });
		Obj->GetPhysXComponent()->SetWorldPosWithParent(float4{ 1116, 140, 5023 });

		// off 상태여야함? 
		std::shared_ptr<Ladder> Obj2 = CreateActor<Ladder>();
		Obj2->GetTransform()->SetLocalRotation(float4{ 0, 45, 0 });
		Obj2->GetPhysXComponent()->SetWorldPosWithParent(float4{ 105, 46, 6140 });
	}
}
