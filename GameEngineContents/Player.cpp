#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>

Player::Player() 
{
}

Player::~Player() 
{
}


void Player::Start()
{
	/*std::shared_ptr<GameEngineFBXRenderer> Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("House1.FBX", "MeshTexture");*/

	std::shared_ptr<GameEngineFBXRenderer> Renderer2 = CreateComponent<GameEngineFBXRenderer>();
	Renderer2->SetFBXMesh("House1.fbx", "MeshTexture");

	//Renderer2->GetTransform()->SetLocalPosition(float4(200, 0, 0));
	float4 Scale = Renderer2->GetTransform()->GetLocalScale();
	Renderer2->GetTransform()->SetLocalScale(Scale * 10.0f);

	// Renderer->SetFBXMesh("AnimMan.FBX", "MeshTexture", 0, 0);
	// Renderer->SetFBXMesh("AnimMan.FBX", "MeshTexture", 0, 2);

}