#include "PrecompileHeader.h"
#include "GameLogo.h"

GameLogo::GameLogo()
{
}

GameLogo::~GameLogo()
{
}

void GameLogo::Start()
{
	LogoRender = CreateComponent<GameEngineUIRenderer>();
	LogoRender->SetTexture("Logo_DeathDoor.png");

	LogoRender->GetTransform()->SetLocalScale({ 592, 394 });
	LogoRender->GetTransform()->SetLocalPosition({ 0, 200 });
}

void GameLogo::Update(float _DeltaTime)
{
}

void GameLogo::Render(float _DeltaTime)
{
}
