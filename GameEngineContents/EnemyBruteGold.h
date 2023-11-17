#pragma once
#include "EnemyBase.h"

// 설명 :
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
		IDLE,  // IDLE
		MOVE,  // WALK, RUN
		SLAM,  // 첫 평타
		SWING, // 후속 평타
		THROW, // 원거리시 불던지기
		BREAK, // 3번째 피격시
		DEATH, // 사망시
		MAX
	};


	void AggroMove(float _DeltaTime);

	std::shared_ptr<class EnemyAttackBox> m_pAttackBox = nullptr;
	float4 m_f4ShootDir = float4::ZERO;
	EnemyBruteGoldState m_ePrevState = EnemyBruteGoldState::MAX;

	int m_iFullHP = 12;
};