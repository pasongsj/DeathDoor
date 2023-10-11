#pragma once
#include "EnemyBase.h"

// 설명 :
class EnemyMage : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyMage();
	~EnemyMage();

	// delete Function
	EnemyMage(const EnemyMage& _Other) = delete;
	EnemyMage(EnemyMage&& _Other) noexcept = delete;
	EnemyMage& operator=(const EnemyMage& _Other) = delete;
	EnemyMage& operator=(EnemyMage&& _Other) noexcept = delete;



protected:
	void InitAniamtion() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	enum class EnemyMageState
	{
		IDLE,
		SHOOT,
		TELEPORT,// 사라짐
		TELEPORT_IN, // 등장
		DEATH,
		MAX
	};

	void TeleportRandPos();

	void SetFSMFUNC();

	float m_fTeleportRange = 300.f;
	float m_fGridRange = 100.f;
	std::vector<float4> vec_RandGrid;
	bool m_bPosSet = false;

	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;
};
