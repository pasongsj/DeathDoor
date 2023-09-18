#include "PrecompileHeader.h"
#include "ContentFBXRenderer.h"

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
			AllUnits[i][j]->SetMaterial("ContentAniMeshDeffered");
			AllUnits[i][j]->ShaderResHelper.SetTexture("MaskTexture", "CrackMask.png");
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
			AllUnits[i][j]->SetMaterial("ContentFade");
			AllUnits[i][j]->ShaderResHelper.SetTexture("FilterTexture", _MaskTextureName);
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

