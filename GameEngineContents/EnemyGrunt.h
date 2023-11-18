#pragma once
#include "EnemyBase.h"

// 설명 :
class EnemyGrunt : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyGrunt();
	~EnemyGrunt();

	// delete Function
	EnemyGrunt(const EnemyGrunt& _Other) = delete;
	EnemyGrunt(EnemyGrunt&& _Other) noexcept = delete;
	EnemyGrunt& operator=(const EnemyGrunt& _Other) = delete;
	EnemyGrunt& operator=(EnemyGrunt&& _Other) noexcept = delete;

	const int GruntFullHP = 3;

protected:
	void InitAnimation() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void SetFSMFUNC() override;


private:
	enum class EnemyGruntState
	{
		IDLE, // IDLE
		MOVE, // WALK, RUN
		JUMP_WAIT,
		JUMP, // JUMP_START, JUMP_MAIN
		HIT, // 공격을 받는경우 HIT
		DEATH, // 죽음 DROWN
		MAX
	};

	void AggroMove(float _DeltaTime);

	std::shared_ptr<class EnemyAttackBox> m_pAttackBox = nullptr;
	float4 m_f4ShootDir = float4::ZERO;
	float4 m_f4TargetPos = float4::ZERO;
	float4 m_f4WaitPos   = float4::ZERO;
	float m_fTargetDistance = 0.f;
	float m_fDistance = 0.f;
	//float StateDuration = 0.0f;
	//bool StateChecker = false;


};
