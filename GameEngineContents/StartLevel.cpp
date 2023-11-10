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
	GetMainCamera()->GetTransform()->SetLocalPosition({ 25.0f, 37.0f, -55.0f });
	GetMainCamera()->GetTransform()->SetLocalRotation({ 28.0f, -30.0f, 0.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	
	Light->GetTransform()->SetWorldRotation({ 100.0f, 40.0f, 0.0f });


	AddPointLight({ .Color = {1.0f, 1.0f, 1.0f},.Position = {-24.0f, 12.0f, 6.0f},.MaxDist = 2.0f,.Intensity = 10.0f });
}

void StartLevel::Update(float _DeltaTime)
{
}

void StartLevel::LevelChangeStart()
{
	CreateActor<Start_BackGround>();
	CreateActor<StartMenu>();

	CreateIMGUIDebugRenderTarget();
	GetMainCamera()->SetNearAndFar(1.0f, 6000.0f);
}

void StartLevel::LevelChangeEnd()
{
	AllActorDestroy();
}
