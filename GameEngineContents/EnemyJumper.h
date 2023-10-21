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

protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

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
		THROW, // BOOMER_THROW, SKIP_THROW
		CATCH, // BOOMER_CATCH, BOOMER_PREP_WAIT
		JUMP, // JUMP
		HIT, //INTERRUPT
		DEATH, // DROWN
		MAX,
	};

	void SetBoomerangPos(BoomerangState _Pos);
	void SetFSMFUNC();

	BoomerangState CurBoomer = BoomerangState::HEAD;


	void IdleUpdate(float _deltaTime);

};

