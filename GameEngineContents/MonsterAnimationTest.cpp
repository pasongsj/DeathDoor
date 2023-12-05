#include "PreCompileHeader.h"
#include "MonsterAnimationTest.h"
#include "Boomerang.h"


MonsterAnimationTest::MonsterAnimationTest()
{
}

MonsterAnimationTest::~MonsterAnimationTest()
{
}

void MonsterAnimationTest::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();
	//Renderer->SetFBXMesh("Health_Plant_MESH.FBX", "ContentAniMeshDeffered");
	Renderer->SetFBXMesh("PLAYER_MESH.FBX", "ContentAniMeshforward", RenderPath::Forward);
	//idle
	Renderer->CreateFBXAnimation("IDLE0", "PLAYER_IDLE_0.FBX", { 0.02f,true });
	Renderer->CreateFBXAnimation("RUN", "PLAYER_RUN.FBX", { 0.02f,true });
	Renderer->ChangeAnimation("RUN");
	//Renderer->SetFBXMesh("_E_GHOUL_MESH.FBX", "ContentAniMeshDeffered", "GoolTexture.png", "GoolTextureOri.png");
	//Renderer->CreateFBXAnimation("RUN_BOW", "_E_GHOUL_RUN_BOW.fbx", { 0.11f,true });
	////Renderer->CreateFBXAnimation("0", "Health_Plant_Growing.fbx", {0.1f });
	////Renderer->CreateFBXAnimation("1", "Health_Plant_Idle.fbx", {0.1f });
	////Renderer->CreateFBXAnimation("2", "Health_Plant_Release.fbx", {0.1f });
	////Renderer->CreateFBXAnimation("3", "Health_Plant_UnGrown.fbx", {0.1f });
	//Renderer->ChangeAnimation("RUN_BOW");
	//Unit = Renderer->GetAllRenderUnit();
	//Unit[0][1]->Off();
	//Renderer->CreateFBXAnimation("4", "FROG_FAT_JUMP_SCREAM.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("5", "FROG_FAT_SHOOT.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("6", "FROG_FAT_SUCK.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("7", "FROG_FAT_SUCK_BOMB.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("8", "FROG_FAT_SUCK_BOMB_GETUP.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("9", "FROG_FAT_SUCK_BOMB_LOOP.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("10", "FROG_FAT_TILT.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("11", "FROG_FAT_TILT_GRABBED.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("12", "FROG_FAT_TILT_JUMP.fbx", {0.1f });
	//Renderer->CreateFBXAnimation("13", "FROG_FAT_TURN.fbx", {0.1f });


	//WeaponRenderer = CreateComponent<ContentFBXRenderer>();
	//WeaponRenderer->SetFBXMesh("FROG_WEAPONMESH.FBX", "ContentMeshDeffered");
	////WeaponRenderer->GetTransform()->SetLocalScale(float4::ONE * 100.0f);
	//WeaponRenderer->GetTransform()->SetParent(Renderer->GetTransform());
	//WeaponRenderer->GetTransform()->SetLocalScale(float4::ONE * 1.4f);
	//WeaponRenderer->SetBone(Renderer.get(), "_FROG_SEPTRE_BONE", float4{0.0f,0.1f,0.0f}, float4{-85.03f,40.0f,0.0f});
	//WeaponRenderer->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 90.0f });
// 
	//WeaponRenderer->GetTransform()->SetLocalScale(float4::ONE * 0.5f);
	//Renderer->CreateFBXAnimation("12", "_E_JUMPER_THROW_Anim.fbx");//
	//Renderer->ChangeAnimation("12");
	GetTransform()->SetLocalScale(float4::ONE * 10.0f);
	GetTransform()->SetLocalRotation(float4{0.0f,0.0f,0.0f});
	//Renderer->GetTransform()->SetLocalRotation({ 10.0f,180.0f, 0.0f });
	GetTransform()->SetLocalPosition(float4{ 0.0f,-200.0f,0.0f });

	if (false == GameEngineInput::IsKey("PressN"))
	{
		GameEngineInput::CreateKey("PressN", 'N');
	}
	if (false == GameEngineInput::IsKey("PressK"))
	{
		GameEngineInput::CreateKey("PressK", 'K');
	}

	//Unit = Renderer->GetAllRenderUnit();
	//
	//Renderer->SetGlowToUnit(0, 0);
	////Renderer->SetUnitColor(0, 0, { 244.0f / 255.0f, 74.0f / 255.0f, 96.0f / 255.0f , 0.2f }, 5);
	////Unit[0][0]->ShaderResHelper.SetTexture("DiffuseTexture", "soulTexture.png");
	///// GetAllRenderUnit()[_IndexY][_IndexX]->ShaderResHelper.SetTexture("CrackTexture", _MaskName);
	//Renderer->SetGlowToUnit(0, 0);
	//Renderer->SetUnitColor(1, 0, float4{ 0.553f,0.027f,0.227f });
	////WeaponRenderer->SetGlowToUnit(1, 0);
	////WeaponRenderer->SetUnitColor(1, 0, { 244.0f / 255.0f, 74.0f / 255.0f, 96.0f / 255.0f , 1.0f }, 5.0f);
	//int a = 0;
	////Renderer->Off();
	//Unit[10][0]->SetMaterial();
	//Unit[23][0]->Off();
	//Renderer->ChangeAnimation("0");
	//Unit[0][0]->Off();
	

}

float4 MonsterAnimationTest::GetBonePos(std::string_view _BoneName)
{
	AnimationBoneData Bone = Renderer->GetBoneData(_BoneName.data());

	std::shared_ptr< GameEngineComponent> BonePivot = CreateComponent< GameEngineComponent>();
	BonePivot->GetTransform()->SetParent(GetTransform());
	BonePivot->GetTransform()->SetLocalPosition(Bone.Pos);

	return BonePivot->GetTransform()->GetWorldPosition();
}


void MonsterAnimationTest::Update(float _DeltaTime)
{
	//float4 pos = Renderer->GetBoneData("_FROG_SEPTRE_BONE").Pos;
	//float4 Rot = Renderer->GetBoneData("_FROG_SEPTRE_BONE").RotEuler;
	//WeaponRenderer->GetTransform()->SetLocalPosition(float4{0.0f,0.1f,0.0f} + pos);
	//WeaponRenderer->GetTransform()->SetLocalRotation(float4{-85.03f,40.0f,0.0f}+ Rot);
	//float4 wpos = WeaponRenderer->GetTransform()->GetWorldPosition();
	//float4 wscale = WeaponRenderer->GetTransform()->GetWorldScale();
	if (true == GameEngineInput::IsDown("PressN"))
	{
		//Renderer->ChangeAnimation("5",true);
		Renderer->ChangeAnimation(std::to_string(index++));
		if (index >= 4)
		{
			index = 0;
		}
	}

	if (true == GameEngineInput::IsDown("PressK"))
	{
		//Unit[mainindex++][0]->On();
		//Unit[mainindex][0]->Off();
		//
		//
		//int a = 0;

	}

	Unit;


	
}






//Renderer->SetFBXMesh("JUMPER_MESH.FBX", "ContentAniMeshDeffered");


//Renderer->CreateFBXAnimation("0", "JUMPER_BOOMER_CATCH.fbx", {0.1f });
//Renderer->SetAnimationStartFunc("0", 0, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//		Renderer->SetRenderUnitControl(14, 0, true);
//	});
//Renderer->SetAnimationStartFunc("0", 28,[this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//		Renderer->SetRenderUnitControl(10, 0, true);
//	});

//Renderer->CreateFBXAnimation("1", "JUMPER_BOOMER_PREP_WAIT.fbx");//
//Renderer->CreateFBXAnimation("2", "JUMPER_BOOMER_THROW.fbx");//

//Renderer->SetAnimationStartFunc("2", 0, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//		Renderer->SetRenderUnitControl(10, 0, true);
//	});
//Renderer->SetAnimationStartFunc("2", 22, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//		Renderer->SetRenderUnitControl(20, 0, true);
//	});
//Renderer->SetAnimationStartFunc("2", 53, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//	});
//Renderer->CreateFBXAnimation("3", "JUMPER_DROWN.fbx");//
//Renderer->CreateFBXAnimation("4", "JUMPER_HOP.fbx");//
//Renderer->CreateFBXAnimation("5", "JUMPER_HOP_LOOP.fbx");
//Renderer->CreateFBXAnimation("6", "JUMPER_IDLE.fbx");//
//Renderer->CreateFBXAnimation("7", "JUMPER_IDLE_LOOK.fbx");//
//Renderer->CreateFBXAnimation("8", "JUMPER_INTERRUPT.fbx");//
//Renderer->CreateFBXAnimation("9", "JUMPER_JUMP.fbx");//
//Renderer->CreateFBXAnimation("10", "JUMPER_POISE_BREAK.fbx");//
//Renderer->CreateFBXAnimation("11", "JUMPER_SKIP_THROW.fbx");//

//Renderer->SetAnimationStartFunc("11", 0, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);

//		Renderer->SetRenderUnitControl(20, 0, true);
//	});
//Renderer->SetAnimationStartFunc("11", 22, [this]
//	{
//		Renderer->SetRenderUnitControl(10, 0, false);
//		Renderer->SetRenderUnitControl(14, 0, false);
//		Renderer->SetRenderUnitControl(20, 0, false);
//	});


//if (Boomer != nullptr)
//{
//	//
//	//float4 BonPos = Renderer->GetBoneData("HEAD").Pos;
//	//BonPos.y += 0.3f;
//	//float4 BoneRot = Renderer->GetBoneData("HEAD").RotEuler;
//	////Boomer->SetBoomer(Boomerang::BoomerType::HEAD, BonPos, /*float4{-180.0f,90.0f,0.0f}*/BoneRot + float4{0.0f,0.0f});
//	//Boomer->SetBoomer(Boomerang::BoomerType::HEAD, BonPos, BoneRot + float4{-180.0f,-90.0f,-90.0f});
//	//
//	//Boomer->GetTransform()->SetLocalPosition(BonPos);
//	////Boomer->GetTransform()->SetWorldRotation(float4{ 90.0f,0.0f,0.0f });
//	//
//	//float4 Pos = Boomer->GetTransform()->GetWorldPosition();
//	//float4 Scale = Boomer->GetTransform()->GetWorldScale();
//}
