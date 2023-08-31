#include "PreCompileHeader.h"
#include "PlayerTestLevel.h"

#include "Player.h"

PlayerTestLevel::PlayerTestLevel()
{
}

PlayerTestLevel::~PlayerTestLevel()
{
}

void PlayerTestLevel::Start()
{

}

void PlayerTestLevel::Update(float _DeltaTime)
{
}


void PlayerTestLevel::LevelChangeStart()
{
	CreateActor<Player>();
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0 });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 50.0f, 0.0f });

}

void PlayerTestLevel::LevelChangeEnd()
{
}
