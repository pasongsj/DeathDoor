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
	Renderer->SetFBXMesh("_E_BRUTE_MESH.FBX", "MeshAniTexture");

	Renderer->CreateFBXAnimation("0", "_E_BRUTE_IDLE.fbx");
	Renderer->CreateFBXAnimation("1", "_E_BRUTE_WALK.fbx");
	Renderer->CreateFBXAnimation("2", "_E_BRUTE_RUN.fbx");
	Renderer->CreateFBXAnimation("3", "_E_BRUTE_SLAM.fbx");
	Renderer->CreateFBXAnimation("4", "_E_BRUTE_SWING.fbx");
	Renderer->CreateFBXAnimation("5", "_E_BRUTE_BREAK.fbx");
	Renderer->CreateFBXAnimation("6", "_E_BRUTE_THROW.fbx");
	//Renderer->ChangeAnimation("0");
	Renderer->GetTransform()->SetLocalScale(float4::ONE * 30.0f);
	Renderer->GetTransform()->SetLocalRotation({ 0.0f,-90.0f, 0.0f });

	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}

}

void MonsterAnimationTest::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PressN"))
	{
		//Renderer->ChangeAnimation("5",true);
		Renderer->ChangeAnimation(std::to_string(index++));
		if (index >= 7)
		{
			index = 0;
		}
	}
}
