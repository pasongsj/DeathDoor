#include "PrecompileHeader.h"
#include "FadeWhite.h"

#include "ContentUIRenderer.h"

FadeWhite::FadeWhite() 
{
}

FadeWhite::~FadeWhite() 
{
}

void FadeWhite::FadeIn()
{	
	if (false == m_bUpdate)
	{
		m_eState = WhiteState::In;
		//m_bUpdate = true;
		m_pSpriteRender->ColorOptionValue.MulColor = float4(1, 1, 1, 1);
	}
	
}

void FadeWhite::FadeOut()
{
	if (false == m_bUpdate)
	{
		m_eState = WhiteState::Out;
		//m_bUpdate = true;
		m_pSpriteRender->ColorOptionValue.MulColor = float4(1, 1, 1, 0);
	}
}

void FadeWhite::Start()
{
	m_pSpriteRender = CreateComponent<ContentUIRenderer>();
	m_pSpriteRender->SetScaleToTexture("blackscreen.png");
	m_pSpriteRender->GetTransform()->SetWorldPosition(float4::ZERO);
	m_pSpriteRender->ColorOptionValue.PlusColor = float4(1, 1, 1, 0);
	m_pSpriteRender->ColorOptionValue.MulColor = float4(1, 1, 1, 0);
}

void FadeWhite::Update(float _DeltaTime)
{
	if (m_bUpdate)
	{
		m_fElapseTime += _DeltaTime;
		switch (m_eState)
		{
		case WhiteState::None:
			return;
			break;
		case WhiteState::In:
			m_pSpriteRender->ColorOptionValue.MulColor = float4(1, 1, 1, 1-m_fElapseTime);
			break;
		case WhiteState::Out:
			m_pSpriteRender->ColorOptionValue.MulColor = float4(1, 1, 1, m_fElapseTime);
			break;
		default:
			break;
		}
		if (m_fElapseTime>=1.f)
		{
			m_fElapseTime = 0.f;
			m_eState = WhiteState::None;
			m_bUpdate = false;
		}
	}
}

