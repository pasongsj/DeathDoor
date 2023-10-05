#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MonsterAnimationTest : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterAnimationTest();
	~MonsterAnimationTest();

	// delete Function
	MonsterAnimationTest(const MonsterAnimationTest& _Other) = delete;
	MonsterAnimationTest(MonsterAnimationTest&& _Other) noexcept = delete;
	MonsterAnimationTest& operator=(const MonsterAnimationTest& _Other) = delete;
	MonsterAnimationTest& operator=(MonsterAnimationTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineFBXRenderer> Renderer = nullptr;
	std::vector<std::string> AnimationName;
	int index = 0;
};

