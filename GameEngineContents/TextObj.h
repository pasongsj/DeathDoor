#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// Ό³Έν :
class TextObj : public GameEngineActor
{
public:
	// constrcuter destructer
	TextObj();
	~TextObj();

	// delete Function
	TextObj(const TextObj& _Other) = delete;
	TextObj(TextObj&& _Other) noexcept = delete;
	TextObj& operator=(const TextObj& _Other) = delete;
	TextObj& operator=(TextObj&& _Other) noexcept = delete;

	void SetTxt(const std::string_view& _Text)
	{
		m_pFontRenderer->SetText(_Text);
	}
	void FadeOn()
	{
		m_bAlpha = true;
	}
	std::shared_ptr<GameEngineFontRenderer> GetRenderer()
	{
		return m_pFontRenderer;
	}

	void SetScale(float _Scale)
	{
		m_fScale = _Scale;
		m_pFontRenderer->SetScale(_Scale);
	}
	void SetPosition(float4 _Pos)
	{
		m_pFontRenderer->GetTransform()->SetLocalPosition(_Pos);
	}

	void SetColor(float4 _Color)
	{
		m_f4Color = { _Color.x / 255.f,_Color.y / 255.f,_Color.z / 255.f,_Color.a / 255.f };
		m_pFontRenderer->SetColor(m_f4Color);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFontRenderer> m_pFontRenderer = nullptr;
	bool m_bAlpha = false;
	float m_fAlpha = 1.f;
	float m_fScale = 75.f;
	float4 m_f4Color = float4::ZERO;
};

