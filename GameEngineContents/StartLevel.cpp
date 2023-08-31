#include "PrecompileHeader.h"
#include "StartLevel.h"
#include "StartMenu.h"
#include "Start_BackGround.h"

StartLevel::StartLevel()
{
}

StartLevel::~StartLevel()
{
}

void StartLevel::Start()
{
	SetLevelType(PacketLevelType::StartLevel);

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 15.0f, -30.0f });
	GetMainCamera()->GetTransform()->SetLocalRotation({ 28.0f, -30.0f, 0.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	//Light->GetTransform()->SetWorldPosition({ 0.0f, 100.0f, -100.0f });

}

void StartLevel::Update(float _DeltaTime)
{
}

void StartLevel::LevelChangeStart()
{
	CreateActor<Start_BackGround>();
	CreateActor<StartMenu>();
}

void StartLevel::LevelChangeEnd()
{
}
