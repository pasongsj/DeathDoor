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
	//Renderer = CreateComponent<ContentFBXRenderer>();
	//Renderer->SetFBXMesh("Hall_Crow3_MESH.FBX", "ContentAniMeshDeffered");
	//
	//Renderer->CreateFBXAnimation("0", "Hall_Crow3_Stretch.fbx");//
	//Renderer->CreateFBXAnimation("1", "Hall_Crow3_Bored.fbx");//
	//Renderer->CreateFBXAnimation("2", "SHORTCUTDOOR_FLOOR.fbx");//
	//Renderer->CreateFBXAnimation("3", "SHORTCUTDOOR_OPEN_INWARD.fbx");//
	//Renderer->CreateFBXAnimation("4", "SHORTCUTDOOR_OPEN_STILL.fbx");//
	//Renderer->CreateFBXAnimation("5", "SHORTCUTDOOR_ROCKED.fbx");
	//Renderer->CreateFBXAnimation("6", "_E_GHOUL_RUN_BOW.fbx");//
	//Renderer->CreateFBXAnimation("7", "_E_GHOUL_RUN_SWORD.fbx");//
	//Renderer->CreateFBXAnimation("8", "_E_GHOUL_SHOOT_BOW.fbx");//
	//Renderer->CreateFBXAnimation("9", "_E_GHOUL_SHOOT_BOW_RAPID.fbx");//
	//Renderer->CreateFBXAnimation("10", "_E_GHOUL_WALK.fbx");//
	//Renderer->ChangeAnimation("12");
	GetTransform()->SetLocalScale(float4::ONE * 10.0f);
	//Renderer->GetTransform()->SetLocalRotation({ 0.0f,180.0f, 0.0f });

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
		if (index >= 6)
		{
			index = 0;
		}
	}
}
