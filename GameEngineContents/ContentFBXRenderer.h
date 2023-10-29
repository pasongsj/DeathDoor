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
	
	void SetFadeMask(const std::string_view& _MaskTextureName = "MaskType2_0.png");
	void SetCrackMask();

	void FadeOut(float _MaxTime, float _DeltaTime);
	void FadeIn(float _MaxTime, float _DeltaTime);

	void SetFBXMesh(const std::string& _MeshName, const std::string _SettingName) override;
	void SetCrackAmount(float _Amount);

	void SetBlurColor(float4 _Color = {0.956f, 0.286f, 0.372f, 1.0f}, float _Intensity = 3.0f)
	{
		BlurColor = _Color * _Intensity;
		BlurColor.a = _Color.a;
	}

	void SetClipData(float4 _ClipData)
	{
		ClipData = _ClipData;
	}

	void SetGlowToUnit(int _IndexY, int _IndexX, const std::string_view& _MaskName = "WholeMask.png")
	{
		GetAllRenderUnit()[_IndexY][_IndexX]->ShaderResHelper.SetTexture("CrackTexture", _MaskName);
		GetAllRenderUnit()[_IndexY][_IndexX]->Mask.UV_MaskingValue = 1.0f;
	}

	void UnitSetTexture(const std::string_view& _SettingName, const std::string_view& _TextureName, int _IndexY, int _IndexX)
	{
		auto Units = GetAllRenderUnit();

		Units[_IndexY][_IndexX]->ShaderResHelper.SetTexture(_SettingName, _TextureName);
	}

	void SetIntensity(float _Intensity)
	{
		auto Units = GetAllRenderUnit();

		for (int i = 0; i < Units.size(); i++)
		{
			for (int j = 0; j < Units[i].size(); j++)
			{
				Units[i][j]->Color.MulColor = { _Intensity, _Intensity, _Intensity };
			}
		}

		Intensity = _Intensity;
	}

	void SetColor(float4 _RGBA, float _Intensity = -1.0f)
	{
		if (_Intensity < 0.0f)
		{
			_Intensity = Intensity;
		}

		auto Units = GetAllRenderUnit();

		for (int i = 0; i < Units.size(); i++)
		{
			for (int j = 0; j < Units[i].size(); j++)
			{
				Units[i][j]->Color.MulColor = float4::ZERONULL;
				Units[i][j]->Color.PlusColor = { _RGBA.x * _Intensity, _RGBA.y * _Intensity, _RGBA.z * _Intensity, _RGBA.a };
			}
		}
	}

	void SetUnitColor(int _Y, int _X, float4 _RGBA, float _Intensity = -1.0f)
	{
		if (_Intensity < 0.0f)
		{
			_Intensity = Intensity;
		}

		auto Units = GetAllRenderUnit();

		Units[_Y][_X]->Color.MulColor = float4::ZERONULL;
		Units[_Y][_X]->Color.PlusColor = { _RGBA.x * _Intensity, _RGBA.y * _Intensity, _RGBA.z * _Intensity, _RGBA.a };
	}

	void SetUnitDiffuseColorIntensity(int _Y, int _X, float _Intensity)
	{
		auto Units = GetAllRenderUnit();

		Units[_Y][_X]->Color.MulColor = { _Intensity , _Intensity , _Intensity, 1.0f };
	}


	void SetReflect();
	void ReflectOff();
	void ReflectOn();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void LinkConstantBuffer();

	float4 BlurColor = {0.85f, 0.26f, 0.33f, -1.0f};
	float4 ClipData = { 0.0f, 0.0f, 1.0f, 1.0f };

	std::string FBXName;
	std::string MaterialName;

	std::shared_ptr<ContentFBXRenderer> ReflectRenderer = nullptr;

	float4 WaterHeight = float4::ZERO;
	float4 CamPos = float4::ZERO;

	float Intensity = 1.0f;
};

