#include "PrecompileHeader.h"
#include "FortressLevel.h"

#include "Player.h"
#include "PhysXCapsuleComponent.h"

#include "Map_Fortress.h"

FortressLevel::FortressLevel()
{
}

FortressLevel::~FortressLevel()
{
}

void FortressLevel::Start()
{
	SetLevelType(PacketLevelType::FortressLevel);
	InitKey();
}

void FortressLevel::Update(float _DeltaTime)
{
	KeyUpdate(_DeltaTime);
}

void FortressLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch_Fortress"))
	{
		GameEngineInput::CreateKey("NaviMesh_Switch_Fortress", 'M');
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
}

void FortressLevel::LevelChangeStart()
{
	CreateScene();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);

	CreateActor<GameEngineLight>();
}

void FortressLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void FortressLevel::LoadMapFBX()
{
	
}

void FortressLevel::Set_StartPos(std::shared_ptr<class Player> _Player)
{
}
