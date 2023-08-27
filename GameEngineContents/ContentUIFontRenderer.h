#pragma once
#include <string_view>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineFont.h>

class ContentUIFontRenderer : public GameEngineRenderer
{
public:
	ContentUIFontRenderer();
	~ContentUIFontRenderer();

	ContentUIFontRenderer(const ContentUIFontRenderer& _Other) = delete;
	ContentUIFontRenderer(ContentUIFontRenderer&& _Other) noexcept = delete;
	ContentUIFontRenderer& operator=(const ContentUIFontRenderer& _Other) = delete;
	ContentUIFontRenderer& operator=(ContentUIFontRenderer&& _Other) noexcept = delete;

	void SetFont(const std::string_view& _Font);
	void SetText(const std::string_view& _Text);

	void SetScale(float _FontScale)
	{
		FontScale = _FontScale;
	}

	void SetColor(float4 _FontColor)
	{
		FontColor = _FontColor;
	}

	inline void SetFontFlag(FW1_TEXT_FLAG _Flag)
	{
		FwTextFlag = _Flag;
	}

protected:
	void Render(float _Delta) override;

private:
	void Start() override;

	std::shared_ptr<GameEngineRenderUnit> Unit;

	float FontScale = 10.0f;
	float4 FontColor = float4::RED;
	std::string Text;
	std::shared_ptr<GameEngineFont> Font;

	FW1_TEXT_FLAG FwTextFlag = FW1_TEXT_FLAG::FW1_TOP;
};

