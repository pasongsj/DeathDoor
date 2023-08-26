#pragma once
#include <GameEngineCore/GameEngineActor.h>

class CharacterList : public GameEngineActor
{

public:

	struct ContentButton
	{
		std::shared_ptr<class GameEngineSpriteRenderer> ButtonRender = nullptr;
		std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
		bool isSelected = false;

		std::string CharacterName = "";
	};

	struct SelectedCharacter
	{
		std::shared_ptr<class GameEngineSpriteRenderer> CircleRender = nullptr;
		std::shared_ptr<class GameEngineFBXRenderer> FocusedCharacter = nullptr;
	};

public:

	CharacterList();
	~CharacterList();

	CharacterList(const CharacterList& _Other) = delete;
	CharacterList(CharacterList&& _Other) noexcept = delete;
	CharacterList& operator=(const CharacterList& _Other) = delete;
	CharacterList& operator=(CharacterList&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _DelTa) override;
private:
	void Create_Character(const std::string_view& _CharacterName);
	void Create_SelectedCharacterCircle();

	void Focus_Character(int _Index);
	void UnFocus_Character(int _Index);

	void SortToCharacter();

	std::vector<std::shared_ptr<ContentButton>> ButtonList;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGroundColor = nullptr;

	SelectedCharacter P1_SelectedCharacter;
	SelectedCharacter P2_SelectedCharacter;
	SelectedCharacter P3_SelectedCharacter;
	SelectedCharacter P4_SelectedCharacter;
};

