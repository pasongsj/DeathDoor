#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BossLevelTestObject : public GameEngineActor
{
public:
	// constrcuter destructer
	BossLevelTestObject();
	~BossLevelTestObject();

	// delete Function
	BossLevelTestObject(const BossLevelTestObject& _Other) = delete;
	BossLevelTestObject(BossLevelTestObject&& _Other) noexcept = delete;
	BossLevelTestObject& operator=(const BossLevelTestObject& _Other) = delete;
	BossLevelTestObject& operator=(BossLevelTestObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXRenderer> TestRenderer = nullptr;

};

