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

	//std::shared_ptr<class PhysXCapsuleComponent> GetPhysXComponent() const
	//{
	//	return m_pCapsuleComp;
	//}

protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;


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

	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;
	void AggroMove(float _DeltaTime);
	void SetFSMFUNC();
	bool CheckHit();

	float StateDuration = 0.0f;
	bool StateChecker = false;
};
