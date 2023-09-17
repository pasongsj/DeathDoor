#include "PreCompileHeader.h"
#include "MonsterAnimationTest.h"

MonsterAnimationTest::MonsterAnimationTest()
{
}

MonsterAnimationTest::~MonsterAnimationTest()
{
}

void MonsterAnimationTest::Start()
{
	Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("_E_MAGE_MESH.FBX", "MeshAniTexture");

	Renderer->CreateFBXAnimation("0", "_E_MAGE_IDLE.fbx");
	Renderer->CreateFBXAnimation("1", "_E_MAGE_SHOOT.fbx");
	Renderer->CreateFBXAnimation("2", "_E_MAGE_SHOOT_THREE.fbx");
	Renderer->CreateFBXAnimation("3", "_E_MAGE_SPIRAL.fbx");
	Renderer->CreateFBXAnimation("4", "_E_MAGE_TELEPORT.fbx");
	Renderer->CreateFBXAnimation("5", "_E_MAGE_TELEPORT_IN.fbx");
	Renderer->CreateFBXAnimation("6", "_E_MAGE_DEATH.fbx");

	Renderer->GetTransform()->SetLocalScale(float4::ONE * 100.0f);
	//Renderer->GetTransform()->SetLocalRotation({ 0.0f,0.0f, -90.0f });

	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}

}

void MonsterAnimationTest::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PressN"))
	{
		Renderer->ChangeAnimation(std::to_string(index++));
		if (index >= 7)
		{
			index = 0;
		}
	}
}
