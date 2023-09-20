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
	Renderer->SetFBXMesh("PLAYER_MESH.FBX", "MeshAniTexture");

	Renderer->CreateFBXAnimation("0", "PLAYER_ARROW.fbx");
	Renderer->CreateFBXAnimation("1", "PLAYER_ARROW_BOMB.fbx");
	Renderer->CreateFBXAnimation("2", "PLAYER_ARROW_BOMB_END.fbx");
	Renderer->CreateFBXAnimation("3", "PLAYER_ARROW_MAGIC.fbx");
	Renderer->CreateFBXAnimation("4", "PLAYER_CHARGE_MAX_L.fbx");
	Renderer->CreateFBXAnimation("5", "PLAYER_CHARGE_MAX_R.fbx");
	Renderer->CreateFBXAnimation("6", "PLAYER_CHARGE_SLASH_L.fbx");
	Renderer->CreateFBXAnimation("7", "PLAYER_CHARGE_SLASH_R.fbx");
	Renderer->CreateFBXAnimation("8", "PLAYER_CLIMBING_LADDER.fbx");
	Renderer->CreateFBXAnimation("9", "PLAYER_CLIMBING_LADDER_DOWN.fbx");
	Renderer->CreateFBXAnimation("10", "PLAYER_CLIMBING_OFF_LADDER_TOP.fbx");
	Renderer->CreateFBXAnimation("11", "PLAYER_DROWN.fbx");
	Renderer->CreateFBXAnimation("12", "PLAYER_FALLING.fbx");
	Renderer->CreateFBXAnimation("13", "PLAYER_GETITEM.fbx");
	Renderer->CreateFBXAnimation("14", "PLAYER_HIT_BACK.fbx");
	Renderer->CreateFBXAnimation("15", "PLAYER_HIT_IDLE.fbx");
	Renderer->CreateFBXAnimation("16", "PLAYER_HIT_RECOVER.fbx");
	Renderer->CreateFBXAnimation("17", "PLAYER_HOOK_SHOT.fbx");
	Renderer->CreateFBXAnimation("18", "PLAYER_HOOKSHOT_FLY.fbx");
	Renderer->CreateFBXAnimation("19", "PLAYER_IDLE_0.fbx");
	Renderer->CreateFBXAnimation("20", "PLAYER_IDLE_1.fbx");
	Renderer->CreateFBXAnimation("21", "PLAYER_IDLE_FEAR.fbx");
	Renderer->CreateFBXAnimation("22", "PLAYER_INJURED_FALL.fbx");
	Renderer->CreateFBXAnimation("23", "PLAYER_INJURED_GETUP.fbx");
	Renderer->CreateFBXAnimation("24", "PLAYER_INJURED_LAND.fbx");
	Renderer->CreateFBXAnimation("25", "PLAYER_LAND.fbx");
	Renderer->CreateFBXAnimation("26", "PLAYER_PLUNGE.fbx");
	Renderer->CreateFBXAnimation("27", "PLAYER_PLUNGE_LAND.fbx");
	Renderer->CreateFBXAnimation("28", "PLAYER_PUSH_LEVER.fbx");
	Renderer->CreateFBXAnimation("29", "PLAYER_ROLL.fbx");
	Renderer->CreateFBXAnimation("30", "PLAYER_ROLL_HEAVY.fbx");
	Renderer->CreateFBXAnimation("31", "PLAYER_ROLL_SLASH.fbx");
	Renderer->CreateFBXAnimation("32", "PLAYER_ROLL_SLASH_END.fbx");
	Renderer->CreateFBXAnimation("33", "PLAYER_RUN.fbx");
	Renderer->CreateFBXAnimation("34", "PLAYER_SLASH_LIGHT_L.fbx");
	Renderer->CreateFBXAnimation("35", "PLAYER_SLASH_LIGHT_R.fbx");
	Renderer->CreateFBXAnimation("36", "PLAYER_SNEAK.fbx");
	Renderer->CreateFBXAnimation("37", "PLAYER_SNEAK.fbx");
	Renderer->ChangeAnimation("0");
	GetTransform()->SetLocalScale(float4::ONE * 10.0f);
	Renderer->GetTransform()->SetLocalRotation({ 0.0f,180.0f, 0.0f });

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
		if (index >= 38)
		{
			index = 0;
		}
	}
}
