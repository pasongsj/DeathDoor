#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyBruteGold : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyBruteGold();
	~EnemyBruteGold();

	// delete Function
	EnemyBruteGold(const EnemyBruteGold& _Other) = delete;
	EnemyBruteGold(EnemyBruteGold&& _Other) noexcept = delete;
	EnemyBruteGold& operator=(const EnemyBruteGold& _Other) = delete;
	EnemyBruteGold& operator=(EnemyBruteGold&& _Other) noexcept = delete;

protected:

	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class EnemyBruteGoldState
	{
		IDLE, // IDLE
		MOVE, // WALK, RUN
		SLAM,
		SWING, 
		THROW, 
		BREAK, 
		MAX
	};


	void AggroMove(float _DeltaTime);
	void SetFSMFUNC();

	float StateDuration = 0.0f;
	bool StateChecker = false;
};