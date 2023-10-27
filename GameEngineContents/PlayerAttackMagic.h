#pragma once
#include "AttackBase.h"
class PlayerAttackMagic : public AttackBase
{
public:
	// constrcuter destructer
	PlayerAttackMagic() ;
	~PlayerAttackMagic();

	// delete Function
	PlayerAttackMagic(const PlayerAttackMagic& _Other) = delete;
	PlayerAttackMagic(PlayerAttackMagic&& _Other) noexcept = delete;
	PlayerAttackMagic& operator=(const PlayerAttackMagic& _Other) = delete;
	PlayerAttackMagic& operator=(PlayerAttackMagic&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CreateParticle(float _DeltaTime) override;
private:
	float ParticleCount = 0.0f;
};

