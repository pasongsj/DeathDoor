#pragma once
#include "EnemyBase.h"

// ���� :
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


	float4 JumpDir = float4::ZERO;

	void JumpMove(float _DeltaTime);

	void SetBoomerangState(BoomerangState _State);

	void ThrowBoomer();

	void SetFSMFUNC();

	bool CheckBooemrang();

	BoomerangState CurBoomer = BoomerangState::HEAD;


};
