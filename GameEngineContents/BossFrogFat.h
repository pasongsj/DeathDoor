#pragma once
#include "BossFrog.h"

// 설명 :
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

	const float4 WeaponPivotPos = float4{ 0.0f,0.1f,0.0f };
	const float4 WeaponPivotRot = float4{ -85.03f,40.0f,0.0f };
	std::shared_ptr<class ContentFBXRenderer> WeaponRenderer = nullptr;

	bool isRightPattern = true;
	bool isTurned = false;

	//등장->포효->우측으로 점프-> 턴->기울기 ->5개 흡입 ->//SUCK_BOMB- >눈뺑글뻉글->고개 도리도리->올라와->궁디흔들고 왼쪽 점프
	//->턴 ->6번 던지기-> 점프 ->우측점프
	enum class BossFrogFatState
	{
		JUMP_SCREAM,//intro
		IDLE,
		JUMP_TO_WATER,
		JUMP_TO_GROUND,
		TURN,
		TILT,
		SUCK,
		SHOOT,
		SUCK_BOMB,
		MAX,
	};
};
//DIE_LAND", "FROG_F
//DIE_STANDING", "FR
//IDLE", "FROG_FAT_I
//FAT_JUMP", "FROG_F	바닥 to 물 짬푸
//JUMP_SCREAM", "FRO	인트로
//SHOOT", "FROG_FAT_	왼쪽에서 6번 던짐
//SUCK", "FROG_FAT_S	오른쪽에서 발판 5개 먹음
//SUCK_BOMB", "FROG_	흡입 중 폭탄 먹음
//SUCK_BOMB_GETUP",		눈알 빙빙 후 일어남
//SUCK_BOMB_LOOP", "	눈깔 빙빙
//TILT", "FROG_FAT_T	땅 잡기
//TILT_GRABBED", "FR	누르기
//TILT_JUMP", "FROG_	물 to 바닥 잡고 점프 꽈당
//TURN", "FROG_FAT_T
