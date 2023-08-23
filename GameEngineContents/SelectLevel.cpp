#include "PrecompileHeader.h"
#include "SelectLevel.h"
#include "CharacterList.h"


#include "Player_Banana.h"

SelectLevel::SelectLevel()
{
}

SelectLevel::~SelectLevel()
{
}

void SelectLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0.0f, -1000.0f });

	Level_CharacterList = CreateActor<CharacterList>();

}

void SelectLevel::Update(float _DeltaTime)
{
}

void SelectLevel::LevelChangeStart()
{
}

void SelectLevel::LevelChangeEnd()
{
}
