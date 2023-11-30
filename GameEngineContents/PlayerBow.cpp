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
	BowRenderer->SetFBXMesh("BOW_MESH.fbx", "ContentMeshForward");
	BowRenderer->GetTransform()->SetLocalScale(PLAYER_BOW_SCALE);
	BowRenderer->GetTransform()->SetLocalRotation(PLAYER_BOW_DEFAULT_DIR);
	BowRenderer->SetColor({ 0.99f, 0.1f, 0.2f }, 7.0f);
	BowRenderer->GetAllRenderUnit()[0][0]->isLight.X = 0;

}


void PlayerBow::SetTrans(const float4& _Pos, const float4& Rot)
{
	GetTransform()->SetWorldPosition(_Pos);
	GetTransform()->SetWorldRotation(Rot);
}
