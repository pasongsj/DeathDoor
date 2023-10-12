#include "PrecompileHeader.h"
#include "ContentUIRenderer.h"
#include "HpBar.h"
#include "Player.h"

HpBar::HpBar()
{
}

HpBar::~HpBar()
{
}

void HpBar::Start()
{
	HpBarRender = CreateComponent<ContentUIRenderer>();
	HpBarRender->SetScaleToTexture("HpBar.png");
	HpBarRender->GetTransform()->SetLocalPosition({ -470, 390 });
	
	for(int i = 0; i < 4; i++)
	{
		std::shared_ptr<ContentUIRenderer> HpBlock = CreateComponent<ContentUIRenderer>();
		HpBlock->SetScaleToTexture("Hp.png");
		HpBlock->ColorOptionValue.MulColor = { 0.67f, 0.91f, 0.37f, 1.0f };
		HpBlock->GetTransform()->SetLocalPosition({ -546.0f + i * 51.0f, 390.0f, 0.0f });

		HpBlocks.push_back(HpBlock);
	}

	HpBlocks[3]->ColorOptionValue.MulColor = { 0.71f, 1.2f, 0.0f, 1.0f };
}

void HpBar::Update(float _DeltaTime)
{
	HpUpdate();
}

void HpBar::Render(float _DeltaTime)
{

}

void HpBar::HpUpdate()
{
	CurHp = Player::MainPlayer->GetPlayerHP();

	if (CurHp != PrevHp)
	{
		if (CurHp <= 0)
		{
			HpBlocks[0]->SetScaleToTexture("Hp_Empty.png");
			return;
		}

		if (CurHp > MaxHp)
		{
			return;
		}

		for (int i = 0; i < CurHp - 1; i++)
		{
			HpBlocks[i]->SetScaleToTexture("Hp.png");
			HpBlocks[i]->ColorOptionValue.MulColor = { 0.67f, 0.91f, 0.37f, 1.0f };
		}

		for (int i = CurHp; i < MaxHp; i++)
		{
			HpBlocks[i]->SetScaleToTexture("Hp_Empty.png");
		}

		HpBlocks[CurHp - 1]->SetScaleToTexture("Hp.png");
		HpBlocks[CurHp - 1]->ColorOptionValue.MulColor = { 0.71f, 1.2f, 0.0f, 1.0f };

		PrevHp = CurHp;
	}

}