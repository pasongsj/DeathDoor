#include "PrecompileHeader.h"
#include "BlackScreen.h"

#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{
}

void BlackScreen::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>();
	m_pRender->SetScaleToTexture("BlackScreen.png");
}

void BlackScreen::Update(float _DeltaTime)
{
}

