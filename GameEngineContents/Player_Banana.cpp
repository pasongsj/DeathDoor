#include "PrecompileHeader.h"
#include "Player_Banana.h"

Player_Banana::Player_Banana()
{
}

Player_Banana::~Player_Banana()
{
}

void Player_Banana::Start()
{
	//SetMyType("BANANA");

	CreateKey();

}

void Player_Banana::Update(float _Delta)
{
	StatusUpdate();
	PlayerUpdate(_Delta);
}

void Player_Banana::Render(float _Delta)
{
}
