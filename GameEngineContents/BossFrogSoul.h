#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossFrogSoul : public GameEngineActor
{
public:
	// constrcuter destructer
	BossFrogSoul();
	~BossFrogSoul();

	// delete Function
	BossFrogSoul(const BossFrogSoul& _Other) = delete;
	BossFrogSoul(BossFrogSoul&& _Other) noexcept = delete;
	BossFrogSoul& operator=(const BossFrogSoul& _Other) = delete;
	BossFrogSoul& operator=(BossFrogSoul&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	
	std::shared_ptr<class ContentFBXRenderer> Render = nullptr;

};

