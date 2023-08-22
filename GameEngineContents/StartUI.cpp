#include "PrecompileHeader.h"
#include "StartUI.h"
#include "ContentSpriteRenderer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

StartUI::StartUI()
{
}

StartUI::~StartUI()
{
}

void StartUI::Start()
{
	BackGround_Sky = CreateComponent<GameEngineSpriteRenderer>();
	BackGround_Sky->SetScaleToTexture("Sky.png");
	//BackGround_Sky->GetTransform()->SetLocalScale({ 1600.0f, 1600.0f, 0.0f });
	//BackGround_Sky->GetTransform()->AddLocalPosition({ 800.0f, 450.0f, 0.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetScaleToTexture("Start_Ground.png");
	Ground->GetTransform()->SetLocalPosition({ 0, -150.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Cloud = CreateComponent<GameEngineSpriteRenderer>();
	Cloud->SetScaleToTexture("Start_Cloud.png");
	Cloud->GetTransform()->SetLocalPosition({ 0, 150.0f });

	std::shared_ptr<GameEngineSpriteRenderer> WaterMelon = CreateComponent<GameEngineSpriteRenderer>();
	WaterMelon->SetScaleToTexture("Start_WaterMelon.png");
	WaterMelon->GetTransform()->SetLocalPosition({ 200.0f, -150.0f, 0.0f });

	float4 WaterMelonScale = WaterMelon->GetTransform()->GetLocalScale();
	WaterMelon->GetTransform()->SetLocalScale(WaterMelonScale.half());

	WhiteLine_Up = CreateComponent<ContentSpriteRenderer>();
	WhiteLine_Up->SetScaleToTexture("WhiteLine.png");
	WhiteLine_Up->GetTransform()->SetLocalPosition({ 0.0f, 400.0f, 0.0f });
	WhiteLine_Up->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 2.0f });

	float4 Scale_WhiteLine_Up = WhiteLine_Up->GetTransform()->GetLocalScale();
	WhiteLine_Up->GetTransform()->AddLocalScale({ Scale_WhiteLine_Up.x, 0, 0 });

	WhiteLine_Down = CreateComponent<ContentSpriteRenderer>();
	WhiteLine_Down->SetScaleToTexture("WhiteLine.png");
	WhiteLine_Down->GetTransform()->SetLocalPosition({ 0.0f, -400.0f, 0.0f });
	WhiteLine_Down->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 182.0f });

	float4 Scale_WhiteLine_Down = WhiteLine_Down->GetTransform()->GetLocalScale();
	WhiteLine_Down->GetTransform()->AddLocalScale({ Scale_WhiteLine_Down.x, 0, 0 });

	Logo_Boomerang = CreateComponent<GameEngineSpriteRenderer>();
	Logo_Boomerang->SetScaleToTexture("Text_BOOMEANG.png");
	
	float4 Logo_BoomerangScale = Logo_Boomerang->GetTransform()->GetLocalScale();
	Logo_Boomerang->GetTransform()->SetLocalScale(Logo_BoomerangScale * 0.75f);

	Logo_F = CreateComponent<GameEngineSpriteRenderer>();
	Logo_F->SetScaleToTexture("Text_F.png");

	Logo_U = CreateComponent<GameEngineSpriteRenderer>();
	Logo_U->SetScaleToTexture("Text_U.png");

	Logo_Arrow = CreateComponent<GameEngineSpriteRenderer>();
	Logo_Arrow->SetScaleToTexture("Logo_Arrow.png");

	Logo_Arrow->GetTransform()->SetLocalScale({ 725.0f, 121.0f });
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
