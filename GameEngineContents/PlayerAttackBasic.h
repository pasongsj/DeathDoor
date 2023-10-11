#pragma once
#include "PlayerAttackBase.h"
#include "PlayerAttackDefinition.h"

// Ό³Έν :
class PlayerAttackBasic : public PlayerAttackBase
{
public:
	// constrcuter destructer
	PlayerAttackBasic();
	~PlayerAttackBasic();

	// delete Function
	PlayerAttackBasic(const PlayerAttackBasic& _Other) = delete;
	PlayerAttackBasic(PlayerAttackBasic&& _Other) noexcept = delete;
	PlayerAttackBasic& operator=(const PlayerAttackBasic& _Other) = delete;
	PlayerAttackBasic& operator=(PlayerAttackBasic&& _Other) noexcept = delete;

protected:

	void Start() override;

private:

};

