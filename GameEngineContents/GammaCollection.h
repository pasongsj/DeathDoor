#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class GammaCollection : public GameEnginePostProcess
{

public:

	GammaCollection();
	~GammaCollection();

	GammaCollection(const GammaCollection& _Other) = delete;
	GammaCollection(GammaCollection&& _Other) noexcept = delete;
	GammaCollection& operator=(const GammaCollection& _Other) = delete;
	GammaCollection& operator=(GammaCollection&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;
private:
	GameEngineRenderUnit GammaCollectionUnit;
	std::shared_ptr<class GameEngineRenderTarget> GammaCollectionTarget;

	GameEngineRenderUnit MergeUnit;
};

