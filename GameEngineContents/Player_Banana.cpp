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
	SetMyType("BANANA");
	GetTransform()->SetLocalRotation({ -180, 90, 90 });
	
	float4 Scale = GetTransform()->GetLocalScale();
	GetTransform()->SetLocalScale(Scale * 20);

	SetExpression("Face0");
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
