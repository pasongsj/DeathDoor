#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class FXAA : public GameEnginePostProcess
{

public:

	FXAA();
	~FXAA();

	FXAA(const FXAA& _Other) = delete;
	FXAA(FXAA&& _Other) noexcept = delete;
	FXAA& operator=(const FXAA& _Other) = delete;
	FXAA& operator=(FXAA&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	//안티에일리어싱
	std::shared_ptr<GameEngineRenderTarget> FXAATarget;
	GameEngineRenderUnit FXAAUnit;
	GameEngineRenderUnit MergeUnit;
};

