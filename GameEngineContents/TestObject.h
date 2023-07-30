#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestObject : public GameEngineActor
{
public:
	// constrcuter destructer
	TestObject();
	~TestObject();

	// delete Function
	TestObject(const TestObject& _Other) = delete;
	TestObject(TestObject&& _Other) noexcept = delete;
	TestObject& operator=(const TestObject& _Other) = delete;
	TestObject& operator=(TestObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pTestObj = nullptr;

	float m_pSpeed = 200.0f;
};

