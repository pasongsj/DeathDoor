#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXLevel.h"

// 설명 :
class PhysXTestLevel : public PhysXLevel // 반드시 레벨대신 피직스 레벨 받을것
{
public:
	// constrcuter destructer
	PhysXTestLevel();
	~PhysXTestLevel();

	// delete Function
	PhysXTestLevel(const PhysXTestLevel& _Other) = delete;
	PhysXTestLevel(PhysXTestLevel&& _Other) noexcept = delete;
	PhysXTestLevel& operator=(const PhysXTestLevel& _Other) = delete;
	PhysXTestLevel& operator=(PhysXTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	
private:
	std::shared_ptr<class GameEngineActor> m_pTestActor = nullptr;
	std::shared_ptr<class BloomEffect> m_pBloom;

};

