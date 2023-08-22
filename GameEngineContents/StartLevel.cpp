#include "PrecompileHeader.h"
#include "StartLevel.h"
#include "StartUI.h"

StartLevel::StartLevel()
{
}

StartLevel::~StartLevel()
{
}

void StartLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0.0f, -1000.0f });

	CreateActor<StartUI>();
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
