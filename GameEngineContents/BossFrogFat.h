#pragma once
#include "BossFrog.h"

// Ό³Έν :
class BossFrogFat : public BossFrog
{
public:
	// constrcuter destructer
	BossFrogFat();
	~BossFrogFat();

	// delete Function
	BossFrogFat(const BossFrogFat& _Other) = delete;
	BossFrogFat(BossFrogFat&& _Other) noexcept = delete;
	BossFrogFat& operator=(const BossFrogFat& _Other) = delete;
	BossFrogFat& operator=(BossFrogFat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void InitAnimation() override;
	void SetFSMFUNC() override;


private:

	bool isJumpTime = false;

	float4 JumpStartPoint = float4::ZERO;
	float4 JumpP2 = float4::ZERO;
	float4 JumpP3 = float4::ZERO;
	float4 JumpEndPoint = float4::ZERO;
	void CalJumpPoint();

	const float4 WeaponPivotPos = float4{ 0.0f,0.1f,0.0f };
	const float4 WeaponPivotRot = float4{ -85.03f,40.0f,0.0f };
	std::shared_ptr<class ContentFBXRenderer> WeaponRenderer = nullptr;

	bool isRightPattern = true;
	bool isTurned = false;
	int LoopCnt = 0;

	enum class BossFrogFatState
	{
		INTRO,//intro
		IDLE,
		GRABBED_IDLE,
		JUMP_TO_WATER,
		JUMP_TO_GROUND,
		TURN,
		TILT,
		SUCK,
		SHOOT,
		SUCK_BOMB,
		SUCK_BOMB_END,
		MAX,
	};

	float4 GetRandomTilePos();
	float4 GetRandomTileIndex();

	void SuckTile();
};