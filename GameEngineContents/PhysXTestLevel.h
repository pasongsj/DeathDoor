#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXLevel.h"

// Ό³Έν :
class PhysXTestLevel : public PhysXLevel
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


};

