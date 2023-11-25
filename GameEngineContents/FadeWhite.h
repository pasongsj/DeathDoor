#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WhiteState
{
	None,
	In,
	Out,
};
// Ό³Έν :
class FadeWhite : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeWhite();
	~FadeWhite();

	// delete Function
	FadeWhite(const FadeWhite& _Other) = delete;
	FadeWhite(FadeWhite&& _Other) noexcept = delete;
	FadeWhite& operator=(const FadeWhite& _Other) = delete;
	FadeWhite& operator=(FadeWhite&& _Other) noexcept = delete;
	
	void FadeIn();
	void FadeOut();
	void FadeUpdate()
	{
		m_bUpdate = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRenderer> m_pSpriteRender = nullptr;
	bool m_bUpdate = false;
	float m_fElapseTime = 0.f;
	WhiteState m_eState = WhiteState::None;
};

