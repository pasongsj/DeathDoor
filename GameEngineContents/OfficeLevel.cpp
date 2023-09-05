#include "PrecompileHeader.h"
#include "OfficeLevel.h"

#include "Map_Office.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"


OfficeLevel::OfficeLevel()
{
}

OfficeLevel::~OfficeLevel()
{
}

void OfficeLevel::Start()
{
	CreateScene();
	SetLevelType(PacketLevelType::OfficeLevel);
	CreateScene();
}

void OfficeLevel::Update(float _DeltaTime)
{
}

void OfficeLevel::LevelChangeStart()
{

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);


	CreateActor<GameEngineLight>();
	CreateActor<Map_Office>();

	// 플레이어 생성후 Set_StartPos함수 호출하면 해당 위치에 세팅
	std::shared_ptr<Player> Obj = CreateActor<Player>();
	Set_StartPos(Obj);
}

void OfficeLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void OfficeLevel::Set_StartPos(std::shared_ptr<Player> _Player)
{
	if (nullptr == _Player)
	{
		MsgAssert("Player 가 nullptr 입니다.");
		return;
	}

	std::shared_ptr<PhysXCapsuleComponent> Comp = _Player->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}
	
	Comp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, m_StartPos));
}
