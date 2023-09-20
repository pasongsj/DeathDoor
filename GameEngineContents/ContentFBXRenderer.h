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
	
	void SetFade(const std::string_view& _MaskTextureName = "MaskType2_0.png");
	void SetCrack();
	void SetCrackAmount(float _Amount);

	void FadeOut(float _MaxTime, float _DeltaTime);
	void FadeIn(float _MaxTime, float _DeltaTime);

protected:

private:
};

