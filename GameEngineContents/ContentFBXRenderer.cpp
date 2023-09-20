#include "PrecompileHeader.h"
#include "ContentFBXRenderer.h"

#include <GameEngineBase/GameEngineRandom.h>

ContentFBXRenderer::ContentFBXRenderer()
{
}

ContentFBXRenderer::~ContentFBXRenderer()
{
}

void ContentFBXRenderer::SetAllUnitTexture(const std::string_view& _SettingName, const std::string_view& _ImageName)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->ShaderResHelper.SetTexture(_SettingName, _ImageName);
		}
	}
}

void ContentFBXRenderer::SetCrack()
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			int Index = GameEngineRandom::MainRandom.RandomInt(1, 4);

			AllUnits[i][j]->ShaderResHelper.SetTexture("MaskTexture", "CrackMask" + std::to_string(Index) + ".png");
			AllUnits[i][j]->Mask.UV_MaskingValue = 0.0f;
		}
	}
}

void ContentFBXRenderer::SetCrackAmount(float _Amount)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->Mask.UV_MaskingValue = _Amount;
		}
	}
}

void ContentFBXRenderer::SetFade(const std::string_view& _MaskTextureName)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->ShaderResHelper.SetTexture("MaskTexture", _MaskTextureName);
		}
	}
}

/*_MaxTime = ÃÑ ¼Ò¿ä½Ã°£ */
void ContentFBXRenderer::FadeOut(float _MaxTime, float _DeltaTime)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->Fade.Fade += 1.0f / _MaxTime * _DeltaTime;

			if (AllUnits[i][j]->Fade.Fade >= 1.0f)
			{
				AllUnits[i][j]->Fade.Fade = 1.0f;
			}
		}
	}
}

/*_MaxTime = ÃÑ ¼Ò¿ä½Ã°£ */
void ContentFBXRenderer::FadeIn(float _MaxTime, float _DeltaTime)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->Fade.Fade -= 1.0f / _MaxTime * _DeltaTime;

			if (AllUnits[i][j]->Fade.Fade <= 0.0f)
			{
				AllUnits[i][j]->Fade.Fade = 0.0f;
			}
		}
	}
}

