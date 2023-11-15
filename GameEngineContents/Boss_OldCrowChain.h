#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss_OldCrowDefinition.cpp"

class Boss_OldCrowChain : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_OldCrowChain();
	~Boss_OldCrowChain();

	// delete Function
	Boss_OldCrowChain(const Boss_OldCrowChain& _Other) = delete;
	Boss_OldCrowChain(Boss_OldCrowChain&& _Other) noexcept = delete;
	Boss_OldCrowChain& operator=(const Boss_OldCrowChain& _Other) = delete;
	Boss_OldCrowChain& operator=(Boss_OldCrowChain&& _Other) noexcept = delete;

	void SetDefault();
	void OnChainEffect();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsOn = false;

	std::vector<std::shared_ptr<class Content2DRenderer>> ChainRenderers;

	void CreateChainRenderer();

	int OnRendererNumber = 0;

};