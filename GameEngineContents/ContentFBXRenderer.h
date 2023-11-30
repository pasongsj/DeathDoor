#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class ContentFBXRenderer : public GameEngineFBXRenderer
{

public:

	ContentFBXRenderer();
	~ContentFBXRenderer();

	ContentFBXRenderer(const ContentFBXRenderer& _Other) = delete;
	ContentFBXRenderer(ContentFBXRenderer&& _Other) noexcept = delete;
	ContentFBXRenderer& operator=(const ContentFBXRenderer& _Other) = delete;
	ContentFBXRenderer& operator=(ContentFBXRenderer&& _Other) noexcept = delete;

	void SetAllUnitTexture(const std::string_view& _SettingName, const std::string_view& _ImageName);
	
	void SetFadeMask(const std::string_view& _MaskTextureName = "MaskType1_0.png");
	void SetCrackMask(const std::string_view& _MaskTextureName = "CrackMask.png");

	void FadeOut(float _MaxTime, float _DeltaTime);
	void FadeIn(float _MaxTime, float _DeltaTime);

	void SetFBXMesh(const std::string& _Name, std::string _Material, const std::string_view& beforeTex, const std::string_view& TextureName) override;
	void SetFBXMesh(const std::string& _MeshName, const std::string _SettingName, RenderPath _Path = RenderPath::None) override;
	void SetCrackAmount(float _Amount);

	void SetClipData(float4 _ClipData)
	{
		ClipData = _ClipData;
	}

	void UnitSetTexture(const std::string_view& _SettingName, const std::string_view& _TextureName, int _IndexY, int _IndexX)
	{
		std::shared_ptr<GameEngineRenderUnit> CurUnit = GetIndexRenderUnit(_IndexY, _IndexX);
		CurUnit->ShaderResHelper.SetTexture(_SettingName, _TextureName);
	}

	void Off()
	{
		GameEngineFBXRenderer::Off();
		ReflectOff();
	}

	void UnitOff(int _Y, int _X)
	{
		GetAllRenderUnit()[_Y][_X]->Off();
		if (nullptr != ReflectRenderer)
		{
			ReflectRenderer->GetAllRenderUnit()[_Y][_X]->Off();
		}
	}

	void On()
	{
		GameEngineFBXRenderer::On();
		ReflectOn();
	}

	void UnitOn(int _Y, int _X)
	{
		GetAllRenderUnit()[_Y][_X]->On();
		ReflectRenderer->GetAllRenderUnit()[_Y][_X]->On();
	}

	void SetReflectRenderer()
	{
		if (ReflectRenderer == nullptr)
		{
			SetReflect();
		}
	}

	void SetColor(float4 _RGBA = { 0.85f, 0.26f, 0.33f, 1.0f }, float _Intensity = 1.0f)
	{
		auto Units = GetAllRenderUnit();

		for (int i = 0; i < Units.size(); i++)
		{
			for (int j = 0; j < Units[i].size(); j++)
			{
				Units[i][j]->Color.MulColor = float4::ZERONULL;
				Units[i][j]->Color.PlusColor = _RGBA * _Intensity;
				Units[i][j]->Color.PlusColor.a = _RGBA.a;
			}
		}
	}

	void SetTextureColorIntensity(float _Intensity)
	{
		auto Units = GetAllRenderUnit();

		for (int i = 0; i < Units.size(); i++)
		{
			for (int j = 0; j < Units[i].size(); j++)
			{
				Units[i][j]->Color.MulColor = float4{ _Intensity, _Intensity, _Intensity, 1.0f};
			}
		}
	}

	void SetUnitTextureColorIntensity(int _Y, int _X, float _Intensity)
	{
		std::shared_ptr<GameEngineRenderUnit> CurUnit = GetIndexRenderUnit(_Y, _X);

		CurUnit->Color.MulColor = float4{ _Intensity, _Intensity, _Intensity};
	}

	void SetUnitColor(int _Y, int _X, float4 _RGBA, float _Intensity = 1.0f)
	{
		std::shared_ptr<GameEngineRenderUnit> CurUnit = GetIndexRenderUnit(_Y, _X);

		CurUnit->Color.MulColor = float4::ZERONULL;
		CurUnit->Color.PlusColor = { _RGBA.x * _Intensity, _RGBA.y * _Intensity, _RGBA.z * _Intensity, _RGBA.a };
	}

	void SetFadeColor(float4 _RGBA = { 0.85f, 0.26f, 0.33f, 1.0f }, float _Intensity = 1.0f)
	{
		auto Units = GetAllRenderUnit();

		for (int i = 0; i < Units.size(); i++)
		{
			for (int j = 0; j < Units[i].size(); j++)
			{
				Units[i][j]->Fade.R = _RGBA.x * _Intensity;
				Units[i][j]->Fade.G = _RGBA.y * _Intensity;
				Units[i][j]->Fade.B = _RGBA.z * _Intensity;
			}
		}
	}

	void SetUnitFadeColor(int _Y, int _X, float4 _RGBA, float _Intensity = 1.0f)
	{
		std::shared_ptr<GameEngineRenderUnit> CurUnit = GetIndexRenderUnit(_Y, _X);

		CurUnit->Fade.R = _RGBA.x * _Intensity;
		CurUnit->Fade.G = _RGBA.y * _Intensity;
		CurUnit->Fade.B = _RGBA.z * _Intensity;
	}

	void SetCrackColor(float4 _RGBA = { 0.85f, 0.26f, 0.33f, 1.0f }, float _Intensity = 5.0f)
	{
		CrackColor = _RGBA * _Intensity;
		CrackColor.a = 1.0f;
	}

	void CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBXName, const AnimationCreateParams& _Params = { 0.05f,true }, int _Index = 0);
	void ChangeAnimation(const std::string& _AnimationName, bool _Force = false, int _StartFrame = -1, float _BlendTime = -1.0f);
	void ReflectOff();
	void ReflectOn();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void SetReflect();
	void LinkConstantBuffer();

	struct isOn
	{
		int isGamma = true;
		int isHdr = true;
		
		int Padding1;
		int Padding2;
	};

	float4 DefaultColor = {0.85f, 0.26f, 0.33f, 1.0f};
	float4 ClipData = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 CrackColor = { 0.85f * 5.0f , 0.26f * 5.0f, 0.33f * 5.0f, 1.0f };

	std::string FBXName;
	std::string MaterialName;
	RenderPath Path;

	std::shared_ptr<GameEngineFBXRenderer> ReflectRenderer = nullptr;

	float4 WaterHeight = float4::ZERO;
	float4 CamPos = float4::ZERO;

	float Intensity = 1.0f;

	isOn isOnBuffer;
};

