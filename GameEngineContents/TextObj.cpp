#include "PrecompileHeader.h"
#include "TextObj.h"

#include <GameEngineCore/GameEngineFontRenderer.h>

TextObj::TextObj() 
{
}

TextObj::~TextObj() 
{
}

void TextObj::Start()
{
	m_pFontRenderer = CreateComponent<GameEngineFontRenderer>();
	m_pFontRenderer->SetFont("±Ã¼­");
	m_pFontRenderer->SetScale(m_fScale);
	m_pFontRenderer->SetColor(float4::WHITE);
	m_pFontRenderer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
}

void TextObj::Update(float _DeltaTime)
{
}

