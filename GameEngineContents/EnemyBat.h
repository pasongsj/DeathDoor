#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyBat : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyBat();
	~EnemyBat();

	// delete Function
	EnemyBat(const EnemyBat& _Other) = delete;
	EnemyBat(EnemyBat&& _Other) noexcept = delete;
	EnemyBat& operator=(const EnemyBat& _Other) = delete;
	EnemyBat& operator=(EnemyBat&& _Other) noexcept = delete;

	std::shared_ptr<class PhysXCapsuleComponent> GetPhysXComponent() const
	{
		return m_pCapsuleComp;
	}

protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	enum class EnemyBatState
	{
		IDLE,
		FLY,
		BITE,
		SHOCK,
		MAX
	};

	std::shared_ptr<class GameEngineFBXRenderer> BatRender = nullptr;
	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;

	void IdleMove(float _DeltaTime);

	void AggroMove(float _DeltaTime);

	void SetFSMFUNC();

};

