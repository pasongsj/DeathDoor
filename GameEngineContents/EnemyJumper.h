#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyJumper : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyJumper();
	~EnemyJumper();

	// delete Function
	EnemyJumper(const EnemyJumper& _Other) = delete;
	EnemyJumper(EnemyJumper&& _Other) noexcept = delete;
	EnemyJumper& operator=(const EnemyJumper& _Other) = delete;
	EnemyJumper& operator=(EnemyJumper&& _Other) noexcept = delete;

	const int JumperFullHP = 10;


protected:
	void InitAnimation() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void SetFSMFUNC() override;

private:

	enum class BoomerangState
	{
		HEAD,
		LEFT,
		RIGHT,
		AIR,
		MAX
	};

	enum class EnemyJumperState
	{
		IDLE, // IDLE, IDLE_LOOK, HOP
		WAIT, // BOOMER_PREP_WAIT
		THROW, // BOOMER_THROW, SKIP_THROW
		CATCH, // BOOMER_CATCH, 
		JUMP, // JUMP
		HIT, //INTERRUPT
		DEATH, // DROWN
		MAX,
	};


	float4 JumpDir = float4::ZERO;

	void JumpMove(float _DeltaTime);

	void SetBoomerangState(BoomerangState _State);

	bool throw_jump = true;

	void ThrowBoomer();


	bool CheckBoomerang();

	BoomerangState CurBoomer = BoomerangState::HEAD;

	std::shared_ptr<class Boomerang> Boomer = nullptr;
	std::shared_ptr<class EnemyAttackBox> JumpAttack = nullptr;

	float IdleDelayTime = 1.0f;

	void AggroBoomer();
};

