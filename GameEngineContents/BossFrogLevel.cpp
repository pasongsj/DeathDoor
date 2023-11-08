#include "PrecompileHeader.h"
#include "BossFrogLevel.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "Player.h"
#include "Map_Sanctuary.h"
#include "BossFrog.h"
#include "BossFrogMain.h"
#include "BossFrogFat.h"
#include "BossFrogWindow.h"
#include "TileManager.h"

#include "WaterBox.h"
#include "GlowEffect.h"
#include "Ladder.h"

BossFrogLevel::BossFrogLevel()
{
}

BossFrogLevel::~BossFrogLevel()
{
}

void BossFrogLevel::Start()
{	
	SetContentLevelType(ContentLevelType::BossFrogLevel);
	InitKey();
}

void BossFrogLevel::Update(float _DeltaTime)
{
	KeyUpdate(_DeltaTime);

	if (false == isFatPhase && nullptr != m_pBossFrog && true == m_pBossFrog->GetIsFrogDeath())
	{
		SecondPhaseStartTime = GetLiveTime() + 7.0f;
		isFatPhase = true;
	}

	if (0.0f != SecondPhaseStartTime && true == m_pBossFrog->GetIsFrogDeath() && GetLiveTime() > SecondPhaseStartTime)
	{
		m_pBossFrog->Death();
		m_pBossFrog = CreateActor<BossFrogFat>();
		SecondPhaseStartTime = 0.0f;

	}

	if (nullptr != m_pBossFrog && (true == m_pBossFrog->GetIsFrogDeath() || false == m_pBossFrog->IntroDone))
	{
		Player::MainPlayer->CameraControl = false;
		if(false == GetMainCamera()->IsFreeCamera() && true == m_pBossFrog->IntroDone)
		{
			float4 nextPos = m_pBossFrog->GetTransform()->GetWorldPosition();
			nextPos.y += 3000.0f; // 카메라 높이
			float4 xzPos = float4::FORWARD * 3000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad); //xz연산
			xzPos.RotaitonYDeg(m_CameraRot.y);
			nextPos -= xzPos;
			GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(GetMainCamera()->GetTransform()->GetWorldPosition(), nextPos, _DeltaTime));
			GetMainCamera()->GetTransform()->SetWorldRotation(float4::LerpClamp(GetMainCamera()->GetTransform()->GetWorldRotation(), m_CameraRot, _DeltaTime));
		}
	}
	else
	{
		Player::MainPlayer->CameraControl = true;
	}

}

void BossFrogLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch_FrogBoss"))
	{
		GameEngineInput::CreateKey("NaviMesh_Switch_FrogBoss", 'M');
		GameEngineInput::CreateKey("Debug_DestroyTile", '8');
		GameEngineInput::CreateKey("Debug_ResetTile", '9');
		GameEngineInput::CreateKey("R", 'R');
	}
}

void BossFrogLevel::KeyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
		m_pMap.lock()->NaviRenderSwitch();
	}

	if (true == GameEngineInput::IsDown("R"))
	{
		Player::MainPlayer->GetPhysXComponent()->SetWorldPosWithParent(float4(-3634.12842f,-170.f, 3898.349123f));
	}
	if (true == GameEngineInput::IsDown("Debug_DestroyTile"))
	{
		TileManager::MainManager->DestroyTile(1, 1);
		TileManager::MainManager->DestroyTile(2, 1);
		TileManager::MainManager->DestroyTile(2, 2);
	}
	if (true == GameEngineInput::IsDown("Debug_ResetTile"))
	{
		TileManager::MainManager->ResetTile();
	}
}

void BossFrogLevel::LevelChangeStart()
{
	LevelInit({ 3200, 1800, 800, 450 });
	GetGlowEffect()->DoubleBlurOff();

	CreateScene();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(float4{ 0.0f,-45.0f,0.0f });
	GetMainCamera()->GetTransform()->SetLocalPosition(m_TestPos + float4{1000.0f,0.0f, -1000.0f});

	Create_TileManager();

	Create_Light();
	Create_Map();
	Create_Player();
	Create_WaterBox();
	Create_BossFrog();
	Create_TriggerObject();
	
	BossFrogWindow::EditorGUI->On();
}

void BossFrogLevel::LevelChangeEnd()
{
	AllActorDestroy();
	BossFrogWindow::EditorGUI->Off();

}

void BossFrogLevel::Create_Light()
{
	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	Light->GetTransform()->SetLocalRotation(float4{ 50, 100, 0 });
}

void BossFrogLevel::Create_Map()
{
	m_pMap = CreateActor<Map_Sanctuary>();
}

void BossFrogLevel::Create_Player()
{
	std::shared_ptr<Player> Obj = CreateActor<Player>();
	float4 Pos = Obj->GetTransform()->GetWorldPosition();
	Set_PlayerStartPos();
}

void BossFrogLevel::Create_BossFrog()
{
	m_pBossFrog = CreateActor<BossFrogMain>();
	Set_BossStartPos();
}

void BossFrogLevel::Create_WaterBox()
{
	std::shared_ptr<GameEngineActor> Actor = CreateActor<GameEngineActor>();
	std::shared_ptr<WaterBox> Box = Actor->CreateComponent<WaterBox>();
	Box->GetTransform()->SetLocalScale({ 6000, 1, 3800 });
	Box->SetWaterPosition({ -3800, -450, 3850 });
	Box->GetTransform()->SetLocalRotation({ 0.0f, 45.0f , 0.0f });
}

void BossFrogLevel::Create_TriggerObject()
{
	{
		std::shared_ptr<Ladder> NewLadder = GetLevel()->CreateActor<Ladder>();
		NewLadder->GetTransform()->AddLocalRotation(float4{ 0, -45, 0 });
		NewLadder->GetTransform()->SetLocalPosition(float4{ -4880,  -75 , 4947 });
	}
}

void BossFrogLevel::Create_TileManager()
{
	CreateActor<TileManager>();
}

void BossFrogLevel::Set_PlayerStartPos()
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

	Comp->SetWorldPosWithParent(m_StartPos);
}

void BossFrogLevel::Set_BossStartPos()
{
	if (nullptr == m_pBossFrog)
	{
		MsgAssert("Boss 가 nullptr 입니다.");
		return;
	}

	std::shared_ptr<PhysXControllerComponent> Comp = m_pBossFrog->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}

	Comp->SetWorldPosWithParent(m_TestPos);
}

