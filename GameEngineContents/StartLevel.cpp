#include "PrecompileHeader.h"
#include "StartLevel.h"

#include "GameLogo.h"
#include "StartMenu.h"

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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -100.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	CreateActor<GameLogo>();
	CreateActor<StartMenu>();
}

void StartLevel::Update(float _DeltaTime)
{
}

void StartLevel::LevelChangeStart()
{
}

void StartLevel::LevelChangeEnd()
{
}
