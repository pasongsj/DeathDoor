#include "PrecompileHeader.h"
#include "ContentLevel.h"
#include "Mouse.h"
#include "MPBar.h"
#include "HPBar.h"
#include "SkillSlot.h"
#include "FXAA.h"
#include "GammaCorrection.h"
#include "BrightBloomEffect.h"
#include "ToneMapping.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

void ContentLevel::LevelInit(float4 _BlurSize)
{
	CreateUI();
	SetPostPrecessEffect(_BlurSize);
	CreatePivotActor();

#ifdef _DEBUG
	CreateIMGUIDebugRenderTarget();
#endif
}

void ContentLevel::CreateIMGUIDebugRenderTarget()
{
	GameEngineCoreWindow::AddDebugRenderTarget(0, "AllRenderTarget", GetMainCamera()->GetCamAllRenderTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(1, "LightRenderTarget", GetMainCamera()->GetDeferredLightTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(2, "MainCameraForwardTarget", GetMainCamera()->GetCamForwardTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(3, "DeferredTarget", GetMainCamera()->GetCamDeferrdTarget());
}

void ContentLevel::CreateUI()
{
	CreateActor<Mouse>();
	CreateActor<SkillSlot>(); 
	CreateActor<HpBar>();
	CreateActor<MpBar>();
}

void ContentLevel::SetPostPrecessEffect(float4 _BlurSize)
{
	GetLevel()->GetLastTarget()->CreateEffect<BrightBloomEffect>();
	ToneMappingEffect = GetLevel()->GetLastTarget()->CreateEffect<ToneMapping>();
	Gamma = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
	AntiAliasing = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
}

void ContentLevel::CreatePivotActor()
{
	PivotActor = CreateActor<GameEngineActor>();
}

void ContentLevel::GraphicUpdate()
{
	GammaUpdate();
	HDRUpdate();
	FXAAUpdate();
}

void ContentLevel::GammaUpdate()
{
	if (PrevisGamma == isGamma)
	{
		return;
	}

	if (isGamma == true)
	{
		if (Gamma != nullptr)
		{
			MsgAssert("감마보정 효과가 제거되지 않은 상태에서 다시 생성하려고 했습니다.");
			return;
		}

		Gamma = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();

		if (AntiAliasing != nullptr)
		{
			GetLevel()->GetLastTarget()->ReleaseEffect(AntiAliasing);
			AntiAliasing = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
		}
	}
	else
	{
		if (Gamma == nullptr)
		{
			MsgAssert("감마보정 효과가 적용되지 않은 상태에서, 제거하려고 했습니다.");
			return;
		}

		GetLevel()->GetLastTarget()->ReleaseEffect(Gamma);
		Gamma = nullptr;
	}

	PrevisGamma = isGamma;

}

void ContentLevel::HDRUpdate()
{
	if (PrevisHDR == isHDR)
	{
		return;
	}

	if (isHDR == true)
	{
		if (ToneMappingEffect != nullptr)
		{
			MsgAssert("톤매핑 효과가 제거되지 않은 상태에서 다시 적용하려고 하였습니다.");
		}

		ToneMappingEffect = GetLevel()->GetLastTarget()->CreateEffect<ToneMapping>();
		
		if (Gamma != nullptr)
		{
			GetLevel()->GetLastTarget()->ReleaseEffect(Gamma);
			Gamma = GetLevel()->GetLastTarget()->CreateEffect<GammaCorrection>();
		}

		if (AntiAliasing != nullptr)
		{
			GetLevel()->GetLastTarget()->ReleaseEffect(AntiAliasing);
			AntiAliasing = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
		}
	}
	else
	{
		if (ToneMappingEffect == nullptr)
		{
			MsgAssert("톤매핑 효과가 적용되지 않은 상태에서 제거하려고 하였습니다.");
		}

		GetLevel()->GetLastTarget()->ReleaseEffect(ToneMappingEffect);
		ToneMappingEffect = nullptr;
	}

	PrevisHDR = isHDR;
}

void ContentLevel::FXAAUpdate()
{
	if (PrevisFXAA == isFXAA)
	{
		return;
	}

	if (isFXAA == true)
	{
		if (AntiAliasing != nullptr)
		{
			MsgAssert("FXAA 효과가 제거되지 않은 상태에서 다시 생성하려고 했습니다.");
			return;
		}

		AntiAliasing = GetLevel()->GetLastTarget()->CreateEffect<FXAA>();
	}
	else
	{
		if (AntiAliasing == nullptr)
		{
			MsgAssert("FXAA 효과가 적용되지 않은 상태에서, 제거하려고 했습니다.");
			return;
		}

		GetLevel()->GetLastTarget()->ReleaseEffect(AntiAliasing);
		AntiAliasing = nullptr;
	}

	PrevisFXAA = isFXAA;
}

