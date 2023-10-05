#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerAttackRange : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerAttackRange();
	~PlayerAttackRange();

	// delete Function
	PlayerAttackRange(const PlayerAttackRange& _Other) = delete;
	PlayerAttackRange(PlayerAttackRange&& _Other) noexcept = delete;
	PlayerAttackRange& operator=(const PlayerAttackRange& _Other) = delete;
	PlayerAttackRange& operator=(PlayerAttackRange&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//attack box physx
	std::shared_ptr<class PhysXBoxComponent> AttackBoxComponent = nullptr;

	bool IsCollision = false;
	std::atomic_bool ThreadCollisionChecker = false;
};

