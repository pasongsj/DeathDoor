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

void ContentFBXRenderer::Update(float _DeltaTime)
{
	GameEngineFBXRenderer::Update(_DeltaTime);

	CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	WaterHeight.x = GetLevel()->GetWaterHeight();
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

void ContentFBXRenderer::SetCrackMask(const std::string_view& _MaskTextureName)
{
	auto AllUnits = GetAllRenderUnit();

	for (int i = 0; i < AllUnits.size(); i++)
	{
		for (int j = 0; j < AllUnits[i].size(); j++)
		{
			AllUnits[i][j]->ShaderResHelper.SetTexture("CrackTexture", _MaskTextureName);
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

void ContentFBXRenderer::CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBXName, const AnimationCreateParams& _Params, int _Index)
{
	GameEngineFBXRenderer::CreateFBXAnimation(_AnimationName, _AnimationFBXName, _Params, _Index);
	
	if(ReflectRenderer != nullptr)
	{
		ReflectRenderer->GameEngineFBXRenderer::CreateFBXAnimation(_AnimationName, _AnimationFBXName, _Params, _Index);
	}
}

void ContentFBXRenderer::ChangeAnimation(const std::string& _AnimationName, bool _Force, int _StartFrame, float _BlendTime)
{
	GameEngineFBXRenderer::ChangeAnimation(_AnimationName, _Force, _StartFrame, _BlendTime);

	if (ReflectRenderer != nullptr)
	{
		ReflectRenderer->GameEngineFBXRenderer::ChangeAnimation(_AnimationName, _Force, _StartFrame, _BlendTime);
	}
}

void ContentFBXRenderer::SetReflect()
{
	if (GetActor() == nullptr)
	{
		return;
	}

	ReflectRenderer = GetActor()->CreateComponent<GameEngineFBXRenderer>();
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
	else
	{
		return;
	}

	ReflectRenderer->GameEngineFBXRenderer::SetFBXMesh(FBXName, Material.data(), Path);

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

			if (Units[i][j]->ShaderResHelper.IsConstantBuffer("CamPos") == true)
			{
				Units[i][j]->ShaderResHelper.SetConstantBufferLink("CamPos", CamPos);
			}

			if (Units[i][j]->ShaderResHelper.IsConstantBuffer("WaterHeight") == true)
			{
				Units[i][j]->ShaderResHelper.SetConstantBufferLink("WaterHeight", WaterHeight);
			}

			if (Units[i][j]->ShaderResHelper.IsConstantBuffer("CamPos") == true)
			{
				Units[i][j]->ShaderResHelper.SetConstantBufferLink("CamPos", GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition());
			}
		}
	}
}

void ContentFBXRenderer::ReflectOn()
{
	if (ReflectRenderer == nullptr)
	{
		return;
	}

	auto Units = ReflectRenderer->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			ReflectRenderer->On();
		}
	}
}

void ContentFBXRenderer::ReflectOff()
{
	if (ReflectRenderer == nullptr)
	{
		return;
	}

	auto Units = ReflectRenderer->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			ReflectRenderer->Off();
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

			if (AllUnits[i][j]->ShaderResHelper.IsConstantBuffer("WaterHeight") == true)
			{
				AllUnits[i][j]->ShaderResHelper.SetConstantBufferLink("WaterHeight", WaterHeight);
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

void ContentFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, const std::string_view& beforeTex, const std::string_view& TextureName)
{
	std::string UpperSettingName = GameEngineString::ToUpper(_Material);

	if (UpperSettingName != "CONTENTANIMESHDEFFERED" &&
		UpperSettingName != "CONTENTMESHDEFFERED" &&
		UpperSettingName != "CONTENTMESHALPHA")
	{
		//MsgAssert("기본 머티리얼 세팅은 ContentAniMeshDeffered, ContentMeshDeffered, ContentMeshAlpha 중 하나여야 합니다.");
		//return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, beforeTex, TextureName);
	if (UpperSettingName == "CONTENTMESHDEFFERED" || UpperSettingName == "CONTENTMESHFORWARD")
	{
		SetFadeMask();
	}
	else
	{
		SetFadeMask();
		SetCrackMask();
	}

	LinkConstantBuffer();

	FBXName = _Name;
	MaterialName = UpperSettingName;
}


void ContentFBXRenderer::SetFBXMesh(const std::string& _MeshName, const std::string _SettingName, RenderPath _Path)
{
	std::string UpperSettingName = GameEngineString::ToUpper(_SettingName);

	if (UpperSettingName != "CONTENTANIMESHDEFFERED" &&
		UpperSettingName != "CONTENTMESHDEFFERED" &&
		UpperSettingName != "CONTENTMESHALPHA")
	{
		//MsgAssert("기본 머티리얼 세팅은 ContentAniMeshDeffered, ContentMeshDeffered, ContentMeshAlpha 중 하나여야 합니다.");
		//return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_MeshName, _SettingName, _Path);
	
	if (UpperSettingName == "CONTENTMESHDEFFERED" || UpperSettingName == "CONTENTMESHFORWARD" )
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
	Path = _Path;
}

