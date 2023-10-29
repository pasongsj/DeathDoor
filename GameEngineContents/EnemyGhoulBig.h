#pragma once
#include "EnemyBase.h"

// 설명 : InitGhoul를 꼭해줘야 합니다
class EnemyGhoulBig : public EnemyBase
{
public:
	// constrcuter destructer
	EnemyGhoulBig();
	~EnemyGhoulBig();

	// delete Function
	EnemyGhoulBig(const EnemyGhoulBig& _Other) = delete;
	EnemyGhoulBig(EnemyGhoulBig&& _Other) noexcept = delete;
	EnemyGhoulBig& operator=(const EnemyGhoulBig& _Other) = delete;
	EnemyGhoulBig& operator=(EnemyGhoulBig&& _Other) noexcept = delete;

	const int GhoulFullHP = 8;

protected:
	void Start() override;
	void InitAnimation() override;
	void Update(float _DeltaTime) override;
	void SetFSMFUNC() override;

private:

	enum class EnemyGhoulBigState
	{
		IDLE,
		MOVE,
		SHOOT,
		HIT,
		DEATH,
		MAX
	};

	void AggroMove(float _DeltaTime);


	const float Idle_WaitTime = 1.0f;
	float4 ShootDir = float4::ZERO;

	void ShootArrow();


	const float4 ArrowScale = float4{ 3.0f,1.0f,3.0f };
	const float4 ArrowRot = float4{ 0.0f,-0.0f,-90.0f };
	const float4 ArrowPhysXScale = float4{ 0.0f, 100.0f, 10.0f };

};

