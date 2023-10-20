#include "PrecompileHeader.h"
#include "FortressLevel.h"

#include "PhysXCapsuleComponent.h"

#include "Player.h"
#include "Map_Fortress.h"
#include "CullingManager.h"

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

	LevelInit();

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

	std::shared_ptr<PhysXCapsuleComponent> Comp = Player::MainPlayer->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}

	Comp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, m_StartPos));
}

void FortressLevel::Create_Manager()
{
	m_pCullingManager = CreateActor<CullingManager>();
}
