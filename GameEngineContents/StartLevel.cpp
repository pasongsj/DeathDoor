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

}

void StartLevel::Update(float _DeltaTime)
{
	GraphicUpdate();
}

void StartLevel::LevelChangeStart()
{
	CreateActor<Start_BackGround>();
	CreateActor<StartMenu>();

	GetMainCamera()->SetNearAndFar(1.0f, 6000.0f);

	SetLevelType(PacketLevelType::StartLevel);
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 8.0f, 21.0f, -25.0f });
	GetMainCamera()->GetTransform()->SetLocalRotation({ 32.0f, -30.0f, 0.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();

	Light->GetTransform()->SetWorldRotation({ 60.0f, 40.0f, 0.0f });


	AddPointLight({ .Color = {1.0f, 1.0f, 1.0f},.Position = {-24.0f, 12.0f, 6.0f},.MaxDist = 3.0f,.Intensity = 10.0f });


	MainBGM = GameEngineSound::Play("StartLevel_BGM.mp3");
	MainBGM.SetLoop();

	MainBGM.SoundFadeIn(2.0f);
	
}

void StartLevel::LevelChangeEnd()
{
	MainBGM.SoundFadeOut(1.0f);

	AllActorDestroy();
}
