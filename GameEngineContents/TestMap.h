#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestMap : public GameEngineActor
{
public:
	// constrcuter destructer
	TestMap();
	~TestMap();

	// delete Function
	TestMap(const TestMap& _Other) = delete;
	TestMap(TestMap&& _Other) noexcept = delete;
	TestMap& operator=(const TestMap& _Other) = delete;
	TestMap& operator=(TestMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class PhysXBoxComponent> m_pBoxComp = nullptr;
	std::shared_ptr<GameEngineFBXRenderer> m_pRenderer = nullptr;
};
