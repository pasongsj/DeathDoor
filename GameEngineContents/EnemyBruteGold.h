#pragma once
#include "EnemyBase.h"

// ���� :
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

	void InitAnimation() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void SetFSMFUNC() override;

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

	//float StateDuration = 0.0f;
	//bool StateChecker = false;
};