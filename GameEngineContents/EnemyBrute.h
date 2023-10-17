#pragma once
#include "EnemyBase.h"

// 설명 :
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
		IDLE,  // IDLE
		MOVE,  // WALK, RUN
		SLAM,  // 첫 평타
		SWING, // 후속 평타
		THROW, // 원거리시 불던지기
		BREAK, // 피격시 모션
		MAX
	};


	void AggroMove(float _DeltaTime);
	void SetFSMFUNC();
	
	std::shared_ptr<class EnemyAttackBox> m_pAttackBox = nullptr;
	float4 m_f4ShootDir = float4::ZERO;
};