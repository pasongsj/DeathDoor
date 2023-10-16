#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class SwordTrailRenderer : public GameEngineFBXRenderer
{

public:

	SwordTrailRenderer();
	~SwordTrailRenderer();

	SwordTrailRenderer(const SwordTrailRenderer& _Other) = delete;
	SwordTrailRenderer(SwordTrailRenderer&& _Other) noexcept = delete;
	SwordTrailRenderer& operator=(const SwordTrailRenderer& _Other) = delete;
	SwordTrailRenderer& operator=(SwordTrailRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _MeshName, const std::string _SettingName, bool isRight);
	
	void SetClipData(float _Delta)
	{
		ClipData.x = _Delta;
	}

	void AddClipData(float _Delta)
	{
		ClipData.x += _Delta;
	}

	float GetClipData()
	{
		return ClipData.x;
	}

protected:
	void Start() override;
private:
	float4 ClipData = {0.0f, 0.0f};
};

