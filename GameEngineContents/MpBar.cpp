#include "PrecompileHeader.h"
#include "MpBar.h"
#include "ContentUIRenderer.h"

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

}

void MpBar::Render(float _DeltaTtime)
{

}

void MpBar::ReduceMp()
{
	if (CurMp <= 1)
	{
		MpBlocks[CurMp - 1]->SetScaleToTexture("Mp_Empty.png");
		return;
	}

	MpBlocks[CurMp - 1]->SetScaleToTexture("Mp_Empty.png");
	CurMp--;
	MpBlocks[CurMp - 1]->SetScaleToTexture("Mp_Usable.png");
}