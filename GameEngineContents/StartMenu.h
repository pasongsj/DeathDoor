#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StartMenu : public GameEngineActor
{

public:

	StartMenu();
	~StartMenu();

	StartMenu(const StartMenu& _Other) = delete;
	StartMenu(StartMenu&& _Other) noexcept = delete;
	StartMenu& operator=(const StartMenu& _Other) = delete;
	StartMenu& operator=(StartMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	struct MenuButton{
		std::shared_ptr<class ContentUIFontRenderer> Text = nullptr;
		std::shared_ptr<class GameEngineCollision> Collision = nullptr;
		std::function<void()> ColEvent = nullptr;
		std::function<void()> ClickEvent = nullptr;

		bool isSelected = false;
	};

	void Set_SelectedTexture();
	void Set_MenuButton();
	void CreateKey();

	void Move_SelectedTexture(float _DeltaTime);

	void SelectMenu();

	std::shared_ptr<class GameEngineUIRenderer> Selected_Left = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> Selected_Right = nullptr;
	float MoveAngle = 0.0f;

	std::vector<std::shared_ptr<MenuButton>> MenuButtonList;
	size_t ButtonIndex = 0;
};

