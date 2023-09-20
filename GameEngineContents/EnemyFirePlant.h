#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class EnemyFirePlant : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyFirePlant();
	~EnemyFirePlant();

	// delete Function
	EnemyFirePlant(const EnemyFirePlant& _Other) = delete;
	EnemyFirePlant(EnemyFirePlant&& _Other) noexcept = delete;
	EnemyFirePlant& operator=(const EnemyFirePlant& _Other) = delete;
	EnemyFirePlant& operator=(EnemyFirePlant&& _Other) noexcept = delete;

	std::shared_ptr<class PhysXCapsuleComponent> GetPhysXComponent() const
	{
		return m_pCapsuleComp;
	}
protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class EnemyFireFlowerState
	{
		IDLE,
		BITE,
		DIE,
		MAX
	};

	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;

	void SetFSMFUNC();
};

