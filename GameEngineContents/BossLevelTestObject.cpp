#include "PreCompileHeader.h"

#include "BossLevelTestObject.h"
#include "Boss_OldCrow.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

BossLevelTestObject::BossLevelTestObject() 
{
}

BossLevelTestObject::~BossLevelTestObject() 
{
}

void BossLevelTestObject::Start()
{
	TestRenderer = CreateComponent<GameEngineFBXRenderer>();
	TestRenderer->SetFBXMesh("OldCrow.fbx", "MeshAniTexture");

	TestRenderer->CreateFBXAnimation("OldCrow_Idle", "OldCrow_Idle.fbx", { 0.01f, true });

	TestRenderer->ChangeAnimation("OldCrow_Idle");

	TestRenderer->GetTransform()->AddLocalScale({ 10, 10, 10 });
}

void BossLevelTestObject::Update(float _DeltaTime)
{

}