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
		MOVE,
		HIT,
		TELEPORT,// 사라짐
		TELEPORT_IN, // 등장
		DEATH,
		MAX
	};

	void TeleportRandPos();

	void SetFSMFUNC();

	float m_fTPWaitTime = 2.f;
	float m_fTeleportRange = 750.f;
	float m_fGridRange = 300.f;
	std::vector<float4> m_vecRandGrid;
	UINT m_iCheckCount = 0;

	float4 ShootDir = float4::ZERO;
	float4 m_f4RenderScale = float4::ZERO;
	float m_fScaleRatio = 0.f;
	float m_fWaitTime = 1.f;

	bool m_bCheckPlayer = false;
	bool m_bShoot = false;
};
