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
	MonsterAnimationTest& operator=(const MonsterAnimationTest& _Other) = delete;
	MonsterAnimationTest& operator=(MonsterAnimationTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 GetBonePos(const std::string_view& _BoneName);

	std::shared_ptr<class ContentFBXRenderer> Renderer = nullptr;
	std::shared_ptr<class Boomerang> Boomer = nullptr;
	std::vector<std::string> AnimationName;
	int index = 0;

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> Unit;
	int mainindex = 0;
};

