#pragma once
#include "BossFrog.h"

// ¼³¸í :
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

	//µîÀå->Æ÷È¿->¿ìÃøÀ¸·Î Á¡ÇÁ-> ÅÏ->±â¿ï±â ->5°³ ÈíÀÔ ->//SUCK_BOMB- >´«»±±Û–R±Û->°í°³ µµ¸®µµ¸®->¿Ã¶ó¿Í->±ÃµðÈçµé°í ¿ÞÂÊ Á¡ÇÁ
	//->ÅÏ ->6¹ø ´øÁö±â-> Á¡ÇÁ ->¿ìÃøÁ¡ÇÁ
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
//DIE_LAND", "FROG_F
//DIE_STANDING", "FR
//IDLE", "FROG_FAT_I
//FAT_JUMP", "FROG_F	¹Ù´Ú to ¹° Â«Çª
//JUMP_SCREAM", "FRO	ÀÎÆ®·Î
//SHOOT", "FROG_FAT_	¿ÞÂÊ¿¡¼­ 6¹ø ´øÁü
//SUCK", "FROG_FAT_S	¿À¸¥ÂÊ¿¡¼­ ¹ßÆÇ 5°³ ¸ÔÀ½
//SUCK_BOMB", "FROG_	ÈíÀÔ Áß ÆøÅº ¸ÔÀ½
//SUCK_BOMB_GETUP",		´«¾Ë ºùºù ÈÄ ÀÏ¾î³²
//SUCK_BOMB_LOOP", "	´«±ò ºùºù
//TILT", "FROG_FAT_T	¶¥ Àâ±â
//TILT_GRABBED", "FR	´©¸£±â
//TILT_JUMP", "FROG_	¹° to ¹Ù´Ú Àâ°í Á¡ÇÁ ²Ê´ç
//TURN", "FROG_FAT_T
