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

	// float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();

		// test 
	
	//if (false == GetMainCamera()->IsFreeCamera() && nullptr != BossFrog::MainBoss)
	//{
	//	float4 nextPos = BossFrog::MainBoss->GetTransform()->GetWorldPosition();
	//	nextPos.y += 1000.0f;
	//	nextPos.z -= 1000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad);
	//	GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
	//}
	if (false == GetMainCamera()->IsFreeCamera()) // 계산이 안되서 임시
	{
		float4 nextPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		nextPos.y += 1000.0f; // 카메라 높이
		float4 xzPos = float4::FORWARD * 1000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad); //xz연산
		xzPos.RotaitonYDeg(m_CameraRot.y);
		nextPos -= xzPos;
		GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
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
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);

	CreateActor<TileManager>();

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	Light->GetTransform()->SetLocalRotation(float4{ 50, 100, 0 });

	m_pMap = CreateActor<Map_Sanctuary>();

	std::shared_ptr<Player> Obj = CreateActor<Player>();
	float4 Pos = Obj->GetTransform()->GetWorldPosition();
	Set_PlayerStartPos();

	m_pBossFrog = CreateActor<BossFrogMain>();
	Set_BossStartPos();

	//m_pBossFrog = CreateActor<BossFrogFat>();
	
	BossFrogWindow::EditorGUI->On();

	std::shared_ptr<GameEngineActor> Actor = CreateActor<GameEngineActor>();
	std::shared_ptr<WaterBox> Box = Actor->CreateComponent<WaterBox>();
	Box->GetTransform()->SetLocalScale({ 6000, 1, 3800 });
	Box->SetWaterPosition({-3800, -450, 3850 });
	Box->GetTransform()->SetLocalRotation({ 0.0f, 45.0f , 0.0f});
}

void BossFrogLevel::LevelChangeEnd()
{
	AllActorDestroy();
	BossFrogWindow::EditorGUI->Off();

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

