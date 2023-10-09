#include "PrecompileHeader.h"
#include "FrogBossLevel.h"

#include "PhysXCapsuleComponent.h"
#include "Player.h"
#include "Map_Sanctuary.h"

FrogBossLevel::FrogBossLevel()
{
}

FrogBossLevel::~FrogBossLevel()
{
}

void FrogBossLevel::Start()
{
	InitKey();
}

void FrogBossLevel::Update(float _DeltaTime)
{
	KeyUpdate(_DeltaTime);

	// float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();

		// test 
	if (false == GetMainCamera()->IsFreeCamera())
	{
		GetMainCamera()->GetTransform()->SetWorldPosition(Player::MainPlayer->GetTransform()->GetWorldPosition() + m_CameraPos);
	}
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
		if (nullptr != m_pMap)
		{
			m_pMap->NaviRenderSwitch();
		}
	}
}

void FrogBossLevel::LevelChangeStart()
{
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
}

void FrogBossLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void FrogBossLevel::Set_PlayerStartPos()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("Player 가 nullptr 입니다.");
		return;
	}

	std::shared_ptr<PhysXCapsuleComponent> Comp = Player::MainPlayer->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}

	Comp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, m_StartPos));
}

