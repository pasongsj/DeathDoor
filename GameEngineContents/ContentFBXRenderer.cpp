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

void ContentFBXRenderer::SetCrackMask()
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->ShaderResHelper.SetTexture("MaskTexture", "CrackMask.png");
		}
	}
}

void ContentFBXRenderer::SetFadeMask(const std::string_view& _MaskTextureName)
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

/*_MaxTime = 총 소요시간 */
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

/*_MaxTime = 총 소요시간 */
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

void ContentFBXRenderer::SetFBXMesh(const std::string& _MeshName, const std::string _SettingName)
{
	std::string UpperSettingName = GameEngineString::ToUpper(_SettingName);

	if (UpperSettingName != "CONTENTANIMESHDEFFERED" &&
		UpperSettingName != "CONTENTANIMESHFORWARD" &&
		UpperSettingName != "CONTENTMESHFORWARD")
	{
		MsgAssert("기본 머티리얼 세팅은 ContentAniMeshDeffered, ContentAniMeshForward, ContentMeshForward 중 하나여야 합니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_MeshName, _SettingName);

	SetCrackMask();
	SetFadeMask();
}