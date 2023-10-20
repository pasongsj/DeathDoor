#include "PrecompileHeader.h"
#include "ContentFBXRenderer.h"

#include <GameEngineBase/GameEngineRandom.h>

ContentFBXRenderer::ContentFBXRenderer()
{
}

ContentFBXRenderer::~ContentFBXRenderer()
{
}


void ContentFBXRenderer::Start()
{
	PushCameraRender(0);
}

void ContentFBXRenderer::Render(float _DeltaTime)
{
	//
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
			AllUnits[i][j]->ShaderResHelper.SetTexture("CrackTexture", "CrackMask.png");
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

void ContentFBXRenderer::SetReflect()
{
	if (GetActor() == nullptr)
	{
		return;
	}

	ReflectRenderer = GetActor()->CreateComponent<ContentFBXRenderer>();
	ReflectRenderer->GetTransform()->SetParent(GetTransform());

	std::string_view Material = "";

	if (MaterialName == "CONTENTANIMESHDEFFERED")
	{
		Material = "REFLECTANIMESH";
	}
	else if (MaterialName == "CONTENTMESHDEFFERED")
	{
		Material = "REFLECTMESH";
	}

	ReflectRenderer->GameEngineFBXRenderer::SetFBXMesh(FBXName, Material.data());

	auto Units = ReflectRenderer->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			Units[i][j]->SetReflect();

			if (Units[i][j]->ShaderResHelper.IsConstantBuffer("BlurColor") == true)
			{
				Units[i][j]->ShaderResHelper.SetConstantBufferLink("BlurColor", BlurColor);
			}

			if (Units[i][j]->ShaderResHelper.IsConstantBuffer("ClipData") == true)
			{
				Units[i][j]->ShaderResHelper.SetConstantBufferLink("ClipData", ClipData);
			}
		}
	}
}

void ContentFBXRenderer::ReflectOn()
{
	auto Units = ReflectRenderer->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			ReflectRenderer->On();
			Units[i][j]->SetReflect();
		}
	}
}

void ContentFBXRenderer::ReflectOff()
{
	auto Units = ReflectRenderer->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			ReflectRenderer->Off();
			Units[i][j]->SetReflectOff();
		}
	}
}

void ContentFBXRenderer::LinkConstantBuffer()
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			if (AllUnits[i][j]->ShaderResHelper.IsConstantBuffer("BlurColor") == true)
			{
				AllUnits[i][j]->ShaderResHelper.SetConstantBufferLink("BlurColor", BlurColor);
			}

			if (AllUnits[i][j]->ShaderResHelper.IsConstantBuffer("ClipData") == true)
			{
				AllUnits[i][j]->ShaderResHelper.SetConstantBufferLink("ClipData", ClipData);
			}
		}
	}
}

/*_MaxTime = 총 소요시간 */
void ContentFBXRenderer::FadeOut(float _MaxTime, float _DeltaTime)
{
	if (_MaxTime <= 0.0f)
	{
		_MaxTime = 0.01f;
	}

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
	if (_MaxTime <= 0.0f)
	{
		_MaxTime = 0.01f;
	}

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
		UpperSettingName != "CONTENTMESHDEFFERED")
	{
		MsgAssert("기본 머티리얼 세팅은 ContentAniMeshDeffered, ContentMeshDeffered 중 하나여야 합니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_MeshName, _SettingName);
	
	if (UpperSettingName == "CONTENTMESHDEFFERED")
	{
		SetFadeMask();
	}
	else
	{
		SetFadeMask();
		SetCrackMask();
	}

	LinkConstantBuffer();

	FBXName = _MeshName;
	MaterialName = UpperSettingName;

	SetReflect();
}

