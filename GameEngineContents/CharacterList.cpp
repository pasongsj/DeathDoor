#include "PrecompileHeader.h"
#include "CharacterList.h"

#include  <GameEngineCore/GameEngineSpriteRenderer.h>

CharacterList::CharacterList()
{
}

CharacterList::~CharacterList()
{
}

void CharacterList::Start()
{
	BackGroundColor = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundColor->GetTransform()->SetLocalScale({ 1600, 900 });
	BackGroundColor->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	BackGroundColor->ColorOptionValue.PlusColor = { 0.94f, 0.94f, 0.94f, 1.0f };

	Create_SelectedCharacterCircle();

	ButtonList.reserve(12);

	Create_Character("Avocado");
	Create_Character("Coffee");
	Create_Character("Sushi");
	Create_Character("Carrot");
	Create_Character("Bread");
	Create_Character("Banana");

	Create_Character("Avocado");
	Create_Character("Coffee");
	Create_Character("Sushi");
	Create_Character("Carrot");
	Create_Character("Bread");
	Create_Character("Banana");

	SortToCharacter();
}

void CharacterList::Update(float _Delta)
{
}

void CharacterList::Render(float _DelTa)
{
}

void CharacterList::Create_SelectedCharacterCircle()
{
	P1_SelectedCharacter.CircleRender = CreateComponent<GameEngineSpriteRenderer>();
	P1_SelectedCharacter.CircleRender->SetScaleToTexture("FocusCircle.png");
	P1_SelectedCharacter.CircleRender->GetTransform()->SetLocalPosition({-534, 250});

	P2_SelectedCharacter.CircleRender = CreateComponent<GameEngineSpriteRenderer>();
	P2_SelectedCharacter.CircleRender->SetScaleToTexture("FocusCircle.png");
	P2_SelectedCharacter.CircleRender->GetTransform()->SetLocalPosition({ -178, 250 });

	P3_SelectedCharacter.CircleRender = CreateComponent<GameEngineSpriteRenderer>();
	P3_SelectedCharacter.CircleRender->SetScaleToTexture("FocusCircle.png");
	P3_SelectedCharacter.CircleRender->GetTransform()->SetLocalPosition({ 178, 250 });
	
	P4_SelectedCharacter.CircleRender = CreateComponent<GameEngineSpriteRenderer>();
	P4_SelectedCharacter.CircleRender->SetScaleToTexture("FocusCircle.png");
	P4_SelectedCharacter.CircleRender->GetTransform()->SetLocalPosition({ 534, 250 });

	P1_SelectedCharacter.FocusedCharacter = CreateComponent<GameEngineFBXRenderer>();
}

void CharacterList::Create_Character(const std::string_view& _CharacterName)
{
	std::shared_ptr<ContentButton> NewButton = std::make_shared<ContentButton>();

	NewButton->CharacterName = _CharacterName;

	std::shared_ptr<GameEngineSpriteRenderer> _NewBgRender = CreateComponent<GameEngineSpriteRenderer>();
	_NewBgRender->SetScaleToTexture("CharacterBackGround.png");
	_NewBgRender->ColorOptionValue.MulColor = { 0.74f, 0.74f, 0.74f, 1.0f };

	std::shared_ptr<GameEngineSpriteRenderer> _NewRender = CreateComponent<GameEngineSpriteRenderer>();
	_NewRender->SetScaleToTexture("Select_" + NewButton->CharacterName + "_Idle.png");

	NewButton->BackGround = _NewBgRender;
	NewButton->ButtonRender = _NewRender;

	ButtonList.push_back(NewButton);
}

void CharacterList::Focus_Character(int _Index)
{
	if (ButtonList[_Index]->ButtonRender != nullptr)
	{
		float4 Pos = ButtonList[_Index]->ButtonRender->GetTransform()->GetWorldPosition();
	}

	/*
	크기가 변한다.
	*/
}

void CharacterList::UnFocus_Character(int _Index)
{
	/*
	크기가 돌아온다.
	*/
}

void CharacterList::SortToCharacter()
{
	float StartX = -425.0f;
	float StartY = -300.0f;

	for (int i = 0; i < ButtonList.size(); i++)
	{
		float4 Pos = { StartX + 170.0f * (i % 6), StartY + 170 * (i / 6) };

		ButtonList[i]->ButtonRender->GetTransform()->SetLocalPosition(Pos);
		ButtonList[i]->BackGround->GetTransform()->SetLocalPosition(Pos);
	}
}