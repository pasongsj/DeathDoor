#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss_OldCrowDefinition.cpp"

class Boss_OldCrowEgg : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_OldCrowEgg();
	~Boss_OldCrowEgg();

	// delete Function
	Boss_OldCrowEgg(const Boss_OldCrowEgg& _Other) = delete;
	Boss_OldCrowEgg(Boss_OldCrowEgg&& _Other) noexcept = delete;
	Boss_OldCrowEgg& operator=(const Boss_OldCrowEgg& _Other) = delete;
	Boss_OldCrowEgg& operator=(Boss_OldCrowEgg&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentFBXRenderer> Renderer = nullptr;

};

