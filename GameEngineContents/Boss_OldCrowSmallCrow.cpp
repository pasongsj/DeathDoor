#include "PreCompileHeader.h"

#include "Boss_OldCrowSmallCrow.h"

Boss_OldCrowSmallCrow::Boss_OldCrowSmallCrow() 
{
}

Boss_OldCrowSmallCrow::~Boss_OldCrowSmallCrow() 
{
}

void Boss_OldCrowSmallCrow::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_Egg.FBX", "ContentAniMeshDeffered");
}


void Boss_OldCrowSmallCrow::Update(float _DeltaTime)
{
}