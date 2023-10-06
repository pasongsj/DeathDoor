#pragma once
#include "PlayerAttackBase.h"

// Ό³Έν :
class PlayerAttackArrow : public PlayerAttackBase
{
public:
	// constrcuter destructer
	PlayerAttackArrow();
	~PlayerAttackArrow();

	// delete Function
	PlayerAttackArrow(const PlayerAttackArrow& _Other) = delete;
	PlayerAttackArrow(PlayerAttackArrow&& _Other) noexcept = delete;
	PlayerAttackArrow& operator=(const PlayerAttackArrow& _Other) = delete;
	PlayerAttackArrow& operator=(PlayerAttackArrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

