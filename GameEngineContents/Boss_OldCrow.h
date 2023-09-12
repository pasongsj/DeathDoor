#pragma once
#include <GameEngineContents/EnemyBase.h>

class Boss_OldCrow : public EnemyBase
{
public:
	// constrcuter destructer
	Boss_OldCrow();
	~Boss_OldCrow();

	// delete Function
	Boss_OldCrow(const Boss_OldCrow& _Other) = delete;
	Boss_OldCrow(Boss_OldCrow&& _Other) noexcept = delete;
	Boss_OldCrow& operator=(const Boss_OldCrow& _Other) = delete;
	Boss_OldCrow& operator=(Boss_OldCrow&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;

private:
	enum class Boss_OldCrowState
	{
		IDLE,

		STARTDASH,
		DASH,
		TURNLEFT,
		TURNRIGHT,

		MEGADASHPREP,
		MEGADASH,

		JUMP,
		SLAM,
		SLAMIMPACT,

		EGG,

		SCREAM,
		SCREAMCROWS,
		SCREAMMINI,
				
		TRANSFORM,

		DEATHWHILERUNNING,
		DEATHWHILEUPRIGHT,
	};

	std::map<Boss_OldCrowState, BossStateParameter> StateMap;

	void AnimationInit();
	void StateMachineInit();
	
};

