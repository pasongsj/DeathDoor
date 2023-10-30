#include "PrecompileHeader.h"
#include "FrogBossLevel.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "Player.h"
#include "Map_Sanctuary.h"
#include "BossFrogMain.h"
#include "BossFrogWindow.h"

#include "WaterBox.h"
#include "GlowEffect.h"

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
	if (nullptr != BossFrog::MainBoss)
	{
		float4 nextPos = BossFrog::MainBoss->GetTransform()->GetWorldPosition();
		nextPos.y += 3000.0f;
		nextPos.z -= 3000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad);
		GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
	}
	//if (false == GetMainCamera()->IsFreeCamera()) // 계산이 안되서 임시
	//{
	//	float4 nextPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	//	nextPos.y += 1000.0f; // 카메라 높이
	//	float4 xzPos = float4::FORWARD * 1000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad); //xz연산
	//	xzPos.RotaitonYDeg(m_CameraRot.y);
	//	nextPos -= xzPos;
	//	GetMainCamera()->GetTransform()->SetWorldPosition(nextPos);
	//}
}

void FrogBossLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch_FrogBoss"))
	{
		GameEngineInput::CreateKey("NaviMesh_Switch_FrogBoss", 'M');
	}
}

void FrogBossLevel::KeyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
	
		m_pMap.lock()->NaviRenderSwitch();
		
	}
}

void FrogBossLevel::LevelChangeStart()
{
	LevelInit({ 3200, 1800, 800, 450 });
	GetGlowEffect()->DoubleBlurOff();

	CreateScene();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	Light->GetTransform()->SetLocalRotation(float4{ 50, 100, 0 });

	m_pMap = CreateActor<Map_Sanctuary>();

	std::shared_ptr<Player> Obj = CreateActor<Player>();
	float4 Pos = Obj->GetTransform()->GetWorldPosition();
	Set_PlayerStartPos();

	m_pBossFrog = CreateActor<BossFrogMain>();
	Set_BossStartPos();

	BossFrogWindow::EditorGUI->On();

	std::shared_ptr<GameEngineActor> Actor = CreateActor<GameEngineActor>();
	std::shared_ptr<WaterBox> Box = Actor->CreateComponent<WaterBox>();
	Box->GetTransform()->SetLocalScale({ 10000, 1, 10000 });
	Box->GetTransform()->SetLocalPosition({-4000, -500, 5000 });
	Box->GetTransform()->SetLocalRotation({ 0.0f, 45.0f , 0.0f});
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

void FrogBossLevel::Set_BossStartPos()
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

