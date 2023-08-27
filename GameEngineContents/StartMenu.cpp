#include "PrecompileHeader.h"
#include "ContentUIFontRenderer.h"
#include "StartMenu.h"

StartMenu::StartMenu()
{
}

StartMenu::~StartMenu()
{
}

void StartMenu::Start()
{
	Set_MenuButton();
	Set_SelectedTexture();
	CreateKey();
}

void StartMenu::Update(float _DeltaTime)
{
	Move_SelectedTexture(_DeltaTime);
	SelectMenu();
}

void StartMenu::Render(float _DeltaTime)
{

}

void StartMenu::CreateKey()
{
	if (GameEngineInput::IsKey("MenuDown") == false)
	{
		GameEngineInput::CreateKey("MenuDown", VK_DOWN);
	}

	if (GameEngineInput::IsKey("MenuUp") == false)
	{
		GameEngineInput::CreateKey("MenuUp", VK_UP);
	}
}

void StartMenu::Set_SelectedTexture()
{
	Selected_Left = CreateComponent<GameEngineUIRenderer>();
	Selected_Left->SetScaleToTexture("SelectedMenu.png");
	Selected_Left->GetTransform()->SetLocalScale({ 78.0f, 77.0f, 0.0f });
	Selected_Left->GetTransform()->SetLocalRotation({0.0f, 0.0f, -90.0f});
	Selected_Left->GetTransform()->SetLocalPosition({-150.0f, -185.0f, 0.0f});

	Selected_Right = CreateComponent<GameEngineUIRenderer>();
	Selected_Right->SetScaleToTexture("SelectedMenu.png");
	Selected_Right->GetTransform()->SetLocalScale({ 78.0f, 77.0f, 0.0f });
	Selected_Right->GetTransform()->SetLocalRotation({ 00.0f, 00.0f, 90.0f });
	Selected_Right->GetTransform()->SetLocalPosition({ 150.0f, -185.0f, 0.0f });
}

void StartMenu::Set_MenuButton()
{
	std::shared_ptr<MenuButton> StartButton = std::make_shared<MenuButton>();
	
	StartButton->Text = CreateComponent<ContentUIFontRenderer>();
	StartButton->Text->SetFont("맑은 고딕");
	StartButton->Text->SetText("시작");
	StartButton->Text->SetScale(40.0f);
	StartButton->Text->SetColor({ 0.5f, 0.5f, 0.5f, 1.0f });
	StartButton->Text->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	StartButton->Text->GetTransform()->SetLocalPosition({ 0, -160.0f, 0.0f });

	StartButton->Collision = CreateComponent<GameEngineCollision>();
	StartButton->Collision->GetTransform()->SetLocalScale({ 40, 30 });
	StartButton->Collision->GetTransform()->SetLocalPosition({ 0, -185.0f, 0.0f });
	StartButton->Collision->SetColType(ColType::AABBBOX2D);
	
	//설정해줘야 함.

	//StartButton->Collision->SetOrder();
	
	std::weak_ptr<MenuButton> Weak_St_Bt = StartButton;
	StartButton->ColEvent = [=] 
	{
		if(Weak_St_Bt.lock()->isSelected == false)
		{
			MenuButtonList[ButtonIndex]->isSelected = false;
			ButtonIndex = 0;

			MenuButtonList[ButtonIndex]->isSelected = true;
		}
	};

	StartButton->ClickEvent = [=]
	{
		//메뉴전환
	};

	MenuButtonList.push_back(StartButton);

	std::shared_ptr<MenuButton> ExitButton = std::make_shared<MenuButton>();

	ExitButton->Text = CreateComponent<ContentUIFontRenderer>();
	ExitButton->Text->SetFont("맑은 고딕");
	ExitButton->Text->SetText("종료");
	ExitButton->Text->SetScale(40.0f);
	ExitButton->Text->SetColor({ 0.5f, 0.5f, 0.5f, 1.0f });
	ExitButton->Text->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	ExitButton->Text->GetTransform()->SetLocalPosition({ 0, -250.0f, 0.0f });

	ExitButton->Collision = CreateComponent<GameEngineCollision>();
	ExitButton->Collision->GetTransform()->SetLocalScale({ 40, 30 });
	ExitButton->Collision->GetTransform()->SetLocalPosition({ 0, -275.0f, 0.0f });
	ExitButton->Collision->SetColType(ColType::AABBBOX2D);
	 
	//설정해줘야 함.
	//StartButton->Collision->SetOrder();
	
	std::weak_ptr<MenuButton> Weak_Ex_Bt = ExitButton;
	ExitButton->ColEvent = [=]
	{
		if (Weak_Ex_Bt.lock()->isSelected == false)
		{
			MenuButtonList[ButtonIndex]->isSelected = false;
			ButtonIndex = 1;

			MenuButtonList[ButtonIndex]->isSelected = true;
		}
	};

	ExitButton->ClickEvent = [=]
	{
		exit(0);
	};

	MenuButtonList.push_back(ExitButton);
}


void StartMenu::Move_SelectedTexture(float _DeltaTime)
{
	MoveAngle += 5.0f * _DeltaTime;
	
	if (MoveAngle >= 360.0f)
	{
		MoveAngle -= 360.0f;
	}

	float Sin = sin(MoveAngle);
	float Cos = cos(MoveAngle);

	Selected_Left->GetTransform()->SetLocalPosition({ -150.0f + 7.5f * Cos, -185.0f + ButtonIndex * -90.0f ,  7.5f * Sin});
	Selected_Right->GetTransform()->SetLocalPosition({ 150.0f - 7.5f * Cos, -185.0f + ButtonIndex * -90.0f,  7.5f * Sin });
}

void StartMenu::SelectMenu()
{
	if(GameEngineInput::IsDown("MenuDown") == true)
	{
		if (ButtonIndex < MenuButtonList.size() - 1)
		{
			ButtonIndex++;
			MenuButtonList[ButtonIndex]->isSelected = true;
			MenuButtonList[ButtonIndex - 1]->isSelected = false;
		}
	}

	if (GameEngineInput::IsDown("MenuUp") == true)
	{
		if (ButtonIndex >= 1)
		{
			ButtonIndex--;
			MenuButtonList[ButtonIndex]->isSelected = true;
			MenuButtonList[ButtonIndex + 1]->isSelected = false;
		}
	}

	for (int i = 0; i < MenuButtonList.size(); i++)
	{
		//마우스와 충돌하면 해당 버튼의 ColEvent 실행
	}
}
