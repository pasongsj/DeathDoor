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

	struct MenuButton
	{
		std::shared_ptr<class ContentUIFontRenderer> Text = nullptr;
		std::shared_ptr<class ContentUIFontRenderer> TextShadow = nullptr;
		std::shared_ptr<class GameEngineCollision> Collision = nullptr;
		std::function<void()> ColEvent = nullptr;
		std::function<void()> ClickEvent = nullptr;

		float4 StartPos = { 0.0f, 0.0f, 0.0f };
		bool isSelected = false;
	};

	struct RealStartButton
	{
		std::shared_ptr<class ContentUIRenderer> Window = nullptr;
		std::shared_ptr<class GameEngineCollision> Collision = nullptr;
	};

	void CreateKey();
	
	void Set_Logo();
	void Set_SelectedTexture();
	void Set_MenuButton();
	void Set_RealStartButton();

	void Move_SelectedTexture(float _DeltaTime);
	
	void SelectMenu();

	bool LerpArrowScale(float _DeltaTime);
	bool LerpArrowPos(float _DeltaTime);
	bool HideMenu(float _DeltaTime);
	bool AppearRealStart(float _DeltaTime);

	float4 LeftArrowPos = { 0.0f, 0.0f, 0.0f };
	float4 RightArrowPos = { 0.0f, 0.0f, 0.0f };

	float LerpRatio = 0.0f;
	bool isSelectUpdate = true;
	bool isReady = false;

	std::shared_ptr<class GameEngineUIRenderer> LogoRender = nullptr;

	std::shared_ptr<class ContentUIRenderer> Arrow_Left = nullptr;
	std::shared_ptr<class ContentUIRenderer> Arrow_Right = nullptr;
	float MoveAngle = 0.0f;

	std::function<bool(float)> UpdateFunc = nullptr;

	std::vector<std::shared_ptr<MenuButton>> MenuButtonList;
	std::shared_ptr<RealStartButton> RealStart;

	size_t ButtonIndex = 0;

	std::shared_ptr<class FadeEffect> m_pFadeEffect = nullptr;
	float m_fFadeTime = 1.5f;
	bool m_bIsFadeEffect = false;
};

