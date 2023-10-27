#pragma once
#include "AttackBase.h"

// Ό³Έν :
class PlayerAttackBomb : public AttackBase
{
public:
	// constrcuter destructer
	PlayerAttackBomb();
	~PlayerAttackBomb();

	// delete Function
	PlayerAttackBomb(const PlayerAttackBomb& _Other) = delete;
	PlayerAttackBomb(PlayerAttackBomb&& _Other) noexcept = delete;
	PlayerAttackBomb& operator=(const PlayerAttackBomb& _Other) = delete;
	PlayerAttackBomb& operator=(PlayerAttackBomb&& _Other) noexcept = delete;

	void Death() override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	void CreateParticle(float _DeltaTime) override;
private:
	float ParticleCount = 0.0f;
};

