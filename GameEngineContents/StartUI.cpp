#include "PrecompileHeader.h"
#include "StartUI.h"
#include "ContentSpriteRenderer.h"
#include "ContentUIRenderer.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

StartUI::StartUI()
{
}

StartUI::~StartUI()
{
}

void StartUI::Start()
{
	SetBackGroundObject();
	SetCharacter();
	SetUIobject();
}

void StartUI::Update(float _Delta)
{
	LogoUpdate(_Delta);
}

void StartUI::Render(float _DelTa)
{
}

void StartUI::LogoUpdate(float _Delta)
{
	AddUV += 0.05f * _Delta;

	if (AddUV >= 2.0f)
	{
		AddUV -= 2.0f;
	}

	WhiteLine_Up->SetUVData({ 2, 1, AddUV, 0 });
	WhiteLine_Down->SetUVData({ 2, 1, -AddUV, 0 });

	RotAngle_Logo_Boomerang += 2.0f * _Delta;

	if (RotAngle_Logo_Boomerang >= 180.0f)
	{
		RotAngle_Logo_Boomerang -= 180.0f;
	}

	Logo_Boomerang->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 2.0f * sin(RotAngle_Logo_Boomerang) });

	MoveAngle_Logo_Boomerang += 0.5f * _Delta;

	if (MoveAngle_Logo_Boomerang >= 180.0f)
	{
		MoveAngle_Logo_Boomerang -= 180.0f;
	}

	Logo_Boomerang->GetTransform()->SetLocalPosition({ 0.0f, 270.0f + 15.0f * sin(MoveAngle_Logo_Boomerang), -15.0f * abs(cos(MoveAngle_Logo_Boomerang)) });

	ScaleAngle_Logo_FU += 2.25f * _Delta;

	if (ScaleAngle_Logo_FU >= 180.0f)
	{
		ScaleAngle_Logo_FU -= 180.0f;
	}

	Logo_F->GetTransform()->SetLocalScale({ 243.0f + 15 * (sin(ScaleAngle_Logo_FU)) , 145.0f - 15 * (sin(ScaleAngle_Logo_FU)), 0.0f });
	Logo_U->GetTransform()->SetLocalScale({ 243.0f + 15 * (sin(ScaleAngle_Logo_FU)) , 145.0f - 15 * (sin(ScaleAngle_Logo_FU)), 0.0f });

	float4 Logo_Boomerang_Pos = Logo_Boomerang->GetTransform()->GetLocalPosition();

	float4 Logo_F_Scale = Logo_F->GetTransform()->GetLocalScale();
	float4 Logo_U_Scale = Logo_U->GetTransform()->GetLocalScale();

	Logo_F->GetTransform()->SetLocalPosition(Logo_Boomerang_Pos - float4{ 0, Logo_F_Scale.hy() + 20.0f });
	Logo_U->GetTransform()->SetLocalPosition(Logo_Boomerang_Pos - float4{ 0, Logo_U_Scale.hy() + 20.0f });

	Logo_Arrow->GetTransform()->SetLocalPosition({ 17.0f , Logo_Boomerang_Pos.y - 120.0f, Logo_Boomerang_Pos.z - 1.0f });

}

void StartUI::SetUIobject()
{

	WhiteLine_Up = CreateComponent<ContentUIRenderer>();
	WhiteLine_Up->SetScaleToTexture("WhiteLine.png");
	WhiteLine_Up->GetTransform()->SetLocalPosition({ 0.0f, 400.0f, 0.0f });
	WhiteLine_Up->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 2.0f });

	float4 Scale_WhiteLine_Up = WhiteLine_Up->GetTransform()->GetLocalScale();
	WhiteLine_Up->GetTransform()->AddLocalScale({ Scale_WhiteLine_Up.x, 0, 0 });

	WhiteLine_Down = CreateComponent<ContentUIRenderer>();
	WhiteLine_Down->SetScaleToTexture("WhiteLine.png");
	WhiteLine_Down->GetTransform()->SetLocalPosition({ 0.0f, -400.0f, 0.0f });
	WhiteLine_Down->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 182.0f });

	float4 Scale_WhiteLine_Down = WhiteLine_Down->GetTransform()->GetLocalScale();
	WhiteLine_Down->GetTransform()->AddLocalScale({ Scale_WhiteLine_Down.x, 0, 0 });

	Logo_Boomerang = CreateComponent<GameEngineUIRenderer>();
	Logo_Boomerang->SetScaleToTexture("Text_BOOMEANG.png");

	float4 Logo_BoomerangScale = Logo_Boomerang->GetTransform()->GetLocalScale();
	Logo_Boomerang->GetTransform()->SetLocalScale(Logo_BoomerangScale * 0.75f);

	Logo_F = CreateComponent<GameEngineUIRenderer>();
	Logo_F->SetScaleToTexture("Text_F.png");

	Logo_U = CreateComponent<GameEngineUIRenderer>();
	Logo_U->SetScaleToTexture("Text_U.png");

	Logo_Arrow = CreateComponent<GameEngineUIRenderer>();
	Logo_Arrow->SetScaleToTexture("Logo_Arrow.png");

	Logo_Arrow->GetTransform()->SetLocalScale({ 725.0f, 121.0f });
}

void StartUI::SetBackGroundObject()
{
	BackGround_Sky = CreateComponent<GameEngineSpriteRenderer>();
	BackGround_Sky->SetScaleToTexture("Sky.png");

	std::shared_ptr<GameEngineSpriteRenderer> Ground_Back = CreateComponent<GameEngineSpriteRenderer>();
	Ground_Back->SetScaleToTexture("Start_Ground_Back.png");
	Ground_Back->GetTransform()->SetLocalPosition({ 0, -150.0f });

	std::shared_ptr<GameEngineSpriteRenderer> SmallBamboo_1 = CreateComponent<GameEngineSpriteRenderer>();
	SmallBamboo_1->SetTexture("Start_SmallBamboo.png");
	SmallBamboo_1->GetTransform()->SetLocalScale({ 124,90 });
	SmallBamboo_1->GetTransform()->SetLocalPosition({ -400, -175 });
	SmallBamboo_1->GetTransform()->SetLocalRotation({ 0, 0, -20 });

	std::shared_ptr<GameEngineSpriteRenderer> SmallBamboo_2 = CreateComponent<GameEngineSpriteRenderer>();
	SmallBamboo_2->SetTexture("Start_SmallBamboo.png");
	SmallBamboo_2->GetTransform()->SetLocalScale({ 124,90 });
	SmallBamboo_2->GetTransform()->SetLocalPosition({ -250, -225 });
	SmallBamboo_2->GetTransform()->SetLocalRotation({ 0, 0, -20 });

	std::shared_ptr<GameEngineSpriteRenderer> SmallBamboo_3 = CreateComponent<GameEngineSpriteRenderer>();
	SmallBamboo_3->SetTexture("Start_SmallBamboo.png");
	SmallBamboo_3->GetTransform()->SetLocalScale({ 124,90 });
	SmallBamboo_3->GetTransform()->SetLocalPosition({ -100, -300 });
	SmallBamboo_3->GetTransform()->SetLocalRotation({ 0, 0, -20 });

	std::shared_ptr<GameEngineSpriteRenderer> Ground_Front = CreateComponent<GameEngineSpriteRenderer>();
	Ground_Front->SetScaleToTexture("Start_Ground_Front.png");
	Ground_Front->GetTransform()->SetLocalPosition({ 0, -175.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Ground_Shadow1 = CreateComponent<GameEngineSpriteRenderer>();
	Ground_Shadow1->SetTexture("Start_GroundShadow.png");
	Ground_Shadow1->GetTransform()->SetLocalScale({ 322, 248 });
	Ground_Shadow1->GetTransform()->SetLocalPosition({ -700, -150.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Bamboo1 = CreateComponent<GameEngineSpriteRenderer>();
	Bamboo1->SetTexture("Start_Bamboo1.png");
	Bamboo1->GetTransform()->SetLocalScale({ 150, 278 });
	Bamboo1->GetTransform()->SetLocalPosition({ -800.0f , 200.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Bamboo2 = CreateComponent<GameEngineSpriteRenderer>();
	Bamboo2->SetTexture("Start_Bamboo1.png");
	Bamboo2->GetTransform()->SetLocalScale({ 150, 278 });
	Bamboo2->GetTransform()->SetLocalPosition({ -475.0f , -50.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Cloud = CreateComponent<GameEngineSpriteRenderer>();
	Cloud->SetScaleToTexture("Start_Cloud.png");
	Cloud->GetTransform()->SetLocalPosition({ 0, 150.0f });
	
	std::shared_ptr<GameEngineSpriteRenderer> BigBamboo = CreateComponent<GameEngineSpriteRenderer>();
	BigBamboo->SetTexture("Start_BigBamboo.png");
	BigBamboo->GetTransform()->SetLocalScale({ 260, 478 });
	BigBamboo->GetTransform()->SetLocalPosition({ -750, -400.0f });
}

void StartUI::SetCharacter()
{
	std::shared_ptr<GameEngineSpriteRenderer> WaterMelon = CreateComponent<GameEngineSpriteRenderer>();
	WaterMelon->SetScaleToTexture("Start_WaterMelon.png");
	WaterMelon->GetTransform()->SetLocalPosition({ 200.0f, -150.0f, 0.0f });

	float4 WaterMelonScale = WaterMelon->GetTransform()->GetLocalScale();
	WaterMelon->GetTransform()->SetLocalScale(WaterMelonScale.half());

	float ScaleRatio = 0.8f;

	std::shared_ptr<GameEngineSpriteRenderer> Bread = CreateComponent<GameEngineSpriteRenderer>();
	Bread->SetScaleToTexture("Start_Bread.png");
	Bread->GetTransform()->SetLocalPosition({ -320.0f, -125.0f, 0.0f });
	float4 BreadScale = Bread->GetTransform()->GetLocalScale();
	Bread->GetTransform()->SetLocalScale({ 386.0f, 313.0f , 1.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Avocado = CreateComponent<GameEngineSpriteRenderer>();
	Avocado->SetScaleToTexture("Start_Avocado.png");
	Avocado->GetTransform()->SetLocalPosition({ -650.0f, -30.0f, 0.0f });
	float4 AvocadoScale = Avocado->GetTransform()->GetLocalScale();
	Avocado->GetTransform()->SetLocalScale(AvocadoScale.half() * ScaleRatio);

	std::shared_ptr<GameEngineSpriteRenderer> Banana = CreateComponent<GameEngineSpriteRenderer>();
	Banana->SetScaleToTexture("Start_Banana.png");
	Banana->GetTransform()->SetLocalPosition({ -550.0f, 200.0f, 0.0f });
	float4 BananaScale = Banana->GetTransform()->GetLocalScale();
	Banana->GetTransform()->SetLocalScale(BananaScale.half() * ScaleRatio);

	std::shared_ptr<GameEngineSpriteRenderer> Boomerang_Slash = CreateComponent<GameEngineSpriteRenderer>();
	Boomerang_Slash->SetScaleToTexture("Start_Slash_Effect.png");
	Boomerang_Slash->GetTransform()->SetLocalPosition({ -150.0f, -10.0f, 0.0f });
	float4 Boomerang_SlashScale = Boomerang_Slash->GetTransform()->GetLocalScale();
	Boomerang_Slash->GetTransform()->SetLocalScale(Boomerang_SlashScale);

	std::shared_ptr<GameEngineSpriteRenderer> Boomerang = CreateComponent<GameEngineSpriteRenderer>();
	Boomerang->SetScaleToTexture("Start_Boomerang.png");
	Boomerang->GetTransform()->SetLocalPosition({ 450.0f , -30.0f , 0.0f });
	float4 BoomerangScale = Boomerang->GetTransform()->GetLocalScale();
	Boomerang->GetTransform()->SetLocalScale(BoomerangScale.half());
}