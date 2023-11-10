#include "PreCompileHeader.h"
#include "BossFrogSoul.h"

BossFrogSoul::BossFrogSoul()
{
}

BossFrogSoul::~BossFrogSoul()
{
}

void BossFrogSoul::Start()
{
	Render = CreateComponent<ContentFBXRenderer>();
	Render->SetFBXMesh("FrogSoul.fbx", "ContentMeshDeffered");
	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
}


void BossFrogSoul::Update(float _DeltaTime)
{
}

