#include "PrecompileHeader.h"
#include "CenterLevel.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFont.h>

#include "BlackScreen.h"
#include "LevelWindow.h"

CenterLevel::CenterLevel() 
{
}

CenterLevel::~CenterLevel() 
{
}

void CenterLevel::Start()
{
	SetLevelType(PacketLevelType::CenterLevel);
	GameEngineInput::CreateKey("TestLevel", '0');



	{
		/////test
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

void CenterLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("TestLevel"))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}
}

void CenterLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<BlackScreen> pBG = CreateActor<BlackScreen>(OrderNum::TEST);
	std::shared_ptr<GameEngineSpriteRenderer> pCenterBG = pBG->CreateComponent<GameEngineSpriteRenderer>();
	pCenterBG->SetScaleToTexture("Wait_Texture.png");
}

void CenterLevel::LevelChangeEnd()
{
	AllActorDestroy();
}
