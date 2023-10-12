#include "PrecompileHeader.h"
#include "MpBar.h"
#include "ContentUIRenderer.h"
#include "Player.h"

MpBar::MpBar()
{
}

MpBar::~MpBar()
{
}


void MpBar::Start()
{
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<ContentUIRenderer> MpBlock = CreateComponent<ContentUIRenderer>();
		MpBlock->SetScaleToTexture("Mp.png");
		MpBlock->GetTransform()->SetLocalPosition({ -540.0f + i * 37.0f, 340.0f, 0.0f });

		MpBlocks.push_back(MpBlock);
	}

	MpBlocks[3]->SetScaleToTexture("Mp_Usable.png");
}

void MpBar::Update(float _DeltaTtime)
{
	MpUpdate();
}

void MpBar::Render(float _DeltaTtime)
{

}

void MpBar::MpUpdate()
{
	CurMp = Player::MainPlayer->GetSpellCost();

	if (CurMp != PrevMP)
	{
		if (CurMp <= 0)
		{
			MpBlocks[0]->SetScaleToTexture("Mp_Empty.png");
			return;
		}

		if (CurMp > MaxMp)
		{
			return;
		}

		for (int i = 0; i < CurMp - 1; i++)
		{
			MpBlocks[i]->SetScaleToTexture("Mp.png");
		}

		for (int i = CurMp; i < MaxMp; i++)
		{
			MpBlocks[i]->SetScaleToTexture("Mp_Empty.png");
		}

		MpBlocks[CurMp - 1]->SetScaleToTexture("Mp_Usable.png");

		PrevMP = CurMp;
	}
}
