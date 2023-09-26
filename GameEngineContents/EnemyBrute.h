#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyBrute : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyBrute();
	~EnemyBrute();

	// delete Function
	EnemyBrute(const EnemyBrute& _Other) = delete;
	EnemyBrute(EnemyBrute&& _Other) noexcept = delete;
	EnemyBrute& operator=(const EnemyBrute& _Other) = delete;
	EnemyBrute& operator=(EnemyBrute&& _Other) noexcept = delete;

protected:

	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class EnemyBruteState
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