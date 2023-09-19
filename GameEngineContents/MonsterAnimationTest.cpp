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
	Renderer->SetFBXMesh("_E_GRUNT_MESH.FBX", "MeshAniTexture");

	Renderer->CreateFBXAnimation("0", "_E_GRUNT_IDLE.fbx");
	Renderer->CreateFBXAnimation("1", "_E_GRUNT_DROWN.fbx");
	Renderer->CreateFBXAnimation("2", "_E_GRUNT_WALK.fbx");
	Renderer->CreateFBXAnimation("3", "_E_GRUNT_RUN.fbx");
	Renderer->CreateFBXAnimation("4", "_E_GRUNT_JUMP_START.fbx");
	Renderer->CreateFBXAnimation("5", "_E_GRUNT_JUMP_MAIN.fbx");
	Renderer->CreateFBXAnimation("6", "_E_GRUNT_HIT.fbx");
	Renderer->ChangeAnimation("5");
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
		//Renderer->ChangeAnimation("5",true);
		Renderer->ChangeAnimation(std::to_string(index++));
		if (index >= 7)
		{
			index = 0;
		}
	}
}
