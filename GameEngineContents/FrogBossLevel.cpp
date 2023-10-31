#include "PrecompileHeader.h"
#include "FrogBossLevel.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "Player.h"
#include "Map_Sanctuary.h"
#include "BossFrog.h"
#include "BossFrogMain.h"
#include "BossFrogFat.h"
#include "BossFrogWindow.h"
#include "TileManager.h"

FrogBossLevel::FrogBossLevel()
{
}

FrogBossLevel::~FrogBossLevel()
{
}

void FrogBossLevel::Start()
{	
	SetContentLevelType(ContentLevelType::FrogBossLevel);
	InitKey();
}

void FrogBossLevel::Update(float _DeltaTime)
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
	if (false == GetMainCamera()->IsFreeCamera()) // ����� �ȵǼ� �ӽ�
	{
		float4 nextPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		nextPos.y += 1000.0f; // ī�޶� ����
		float4 xzPos = float4::FORWARD * 1000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad); //xz����
		xzPos.RotaitonYDeg(m_CameraRot.y);
		nextPos -= xzPos;
		GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
	}
}

void FrogBossLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch_FrogBoss"))
	{
		GameEngineInput::CreateKey("NaviMesh_Switch_FrogBoss", 'M');
		GameEngineInput::CreateKey("Debug_DestroyTile", '8');
		GameEngineInput::CreateKey("Debug_ResetTile", '9');
	}
}

void FrogBossLevel::KeyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
		m_pMap.lock()->NaviRenderSwitch();
	}

	if (true == GameEngineInput::IsDown("Debug_DestroyTile"))
	{
		TileManager::MainManager->DestroyTile(2, 2);
	}
	if (true == GameEngineInput::IsDown("Debug_ResetTile"))
	{
		TileManager::MainManager->ResetTile();
	}

}

void FrogBossLevel::LevelChangeStart()
{
	LevelInit({ 3200, 1800, 800, 450 });

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

	//m_pBossFrog = CreateActor<BossFrogMain>();
	//Set_BossStartPos();

	m_pBossFrog = CreateActor<BossFrogFat>();
	
	BossFrogWindow::EditorGUI->On();

}

void FrogBossLevel::LevelChangeEnd()
{
	AllActorDestroy();
	BossFrogWindow::EditorGUI->Off();

}

void FrogBossLevel::Set_PlayerStartPos()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("Player �� nullptr �Դϴ�.");
		return;
	}

	std::shared_ptr<PhysXControllerComponent> Comp = Player::MainPlayer->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player �� PhysXComponent�� nullptr �Դϴ�.");
		return;
	}

	Comp->SetWorldPosWithParent(m_StartPos);
}

void FrogBossLevel::Set_BossStartPos()
{
	if (nullptr == m_pBossFrog)
	{
		MsgAssert("Boss �� nullptr �Դϴ�.");
		return;
	}

	std::shared_ptr<PhysXControllerComponent> Comp = m_pBossFrog->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player �� PhysXComponent�� nullptr �Դϴ�.");
		return;
	}

	Comp->SetWorldPosWithParent(m_TestPos);
}

