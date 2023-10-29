#pragma once
#include "BossFrog.h"

// 설명 : 갑옷을 입고있는 보스로 갑옷을 묶고 있는 끈 3개를 모두 끊으면 다음 페이즈로 넘어간다.

class BossFrogMain : public BossFrog
{
public:
	// constrcuter destructer
	BossFrogMain();
	~BossFrogMain();

	// delete Function
	BossFrogMain(const BossFrogMain& _Other) = delete;
	BossFrogMain(BossFrogMain&& _Other) noexcept = delete;
	BossFrogMain& operator=(const BossFrogMain& _Other) = delete;
	BossFrogMain& operator=(BossFrogMain&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void InitAnimation() override;
	void SetFSMFUNC() override;

private:


	// intro to jump = idle to jump
	// idle to jump
	// swim to jump

	const float IdleStateDuration = 3.0f;

	enum class BossFrogMainState
	{
		IDLE, //IDLE
		INTRO, //POGO_START 포효만 함
		SWIM, // SWIM_EDIT
		DAMAGED, // DAMEGED_LOOP
		IDLE_JUMP_START,	//Idle to jump
		SWIM_JUMP_START,	//swim to jump
		JUMP_LOOP,
		JUMP_END,// SMASH,	
		MAX,
	};

	int JumpCount = 0;
};

