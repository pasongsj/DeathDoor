#include "PrecompileHeader.h"
#include "ContentUIRenderer.h"
#include "HpBar.h"

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
}

void HpBar::Render(float _DeltaTime)
{

}

void HpBar::ReduceHp()
{

	if (CurHp <= 1)
	{
		HpBlocks[CurHp - 1]->SetScaleToTexture("Hp_Empty.png");
		//Á×À½
		return;
	}

	HpBlocks[CurHp - 1]->SetScaleToTexture("Hp_Empty.png");
	CurHp--;

	HpBlocks[CurHp - 1]->ColorOptionValue.MulColor = { 0.71f, 1.2f, 0.0f, 1.0f };
}