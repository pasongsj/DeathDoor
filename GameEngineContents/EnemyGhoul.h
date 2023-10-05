#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyGhoul : public EnemyBase 
{
public:
	// constrcuter destructer
	EnemyGhoul();
	~EnemyGhoul();

	// delete Function
	EnemyGhoul(const EnemyGhoul& _Other) = delete;
	EnemyGhoul(EnemyGhoul&& _Other) noexcept = delete;
	EnemyGhoul& operator=(const EnemyGhoul& _Other) = delete;
	EnemyGhoul& operator=(EnemyGhoul&& _Other) noexcept = delete;


protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	enum class EnemyGhoulState
	{
		IDLE,
		MOVE,
		SHOOT,
		HIT, 
		DEATH,
		MAX
	};

	void AggroMove(float _DeltaTime);
	void SetFSMFUNC();

	//float StateDuration = 0.0f;
	//bool StateChecker = false;
};

