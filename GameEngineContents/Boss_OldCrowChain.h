#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	void Setting(int _Num);
	float4 GetRendererScale();
	void SetDefault();
	void OnRenderer();
	bool GetChainState();
	inline int GetChainNumber()
	{
		return ChainNumber;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) {}

private:
	std::shared_ptr<GameEngineSpriteRenderer> ChainRenderer = nullptr;
	bool IsOn = false;
	int ChainNumber = 0;
};

