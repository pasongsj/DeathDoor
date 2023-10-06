#include "PreCompileHeader.h"
#include "PlayerBow.h"
#include "ContentFBXRenderer.h"
#include "PlayerDefinition.h"

PlayerBow::PlayerBow() 
{
}

PlayerBow::~PlayerBow() 
{
}


void PlayerBow::Start()
{
	BowRenderer = CreateComponent< ContentFBXRenderer>(); // BOW_MESH
	BowRenderer->SetFBXMesh("BOW_MESH.fbx", "ContentMeshDeffered");
	GetTransform()->SetLocalScale(float4::ONE * 200.0f);
}


void PlayerBow::SetTrans(const float4& _Pos, const float4& Rot)
{
	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldRotation(Rot + PLAYER_BOW_DEFAULT_DIR);
}
