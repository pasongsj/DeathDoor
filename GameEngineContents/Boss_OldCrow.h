#pragma once
#include <GameEngineContents/BossBase.h>

class Boss_OldCrow : public BossBase
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

protected:
	void InitAniamtion() override;
	void InitPattern() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class Boss_OldCrowState //스테이트 별
	{
		IDLE,

		//대쉬
		STARTDASH,
		DASH,
		TURN,

		//사슬
		MEGADASHPREP,
		MEGADASH,

		//연속 사슬
		MEGADASH2PREP,
		MEGADASH2,

		//점프
		JUMP,
		SLAM,
		SLAMIMPACT,

		//Egg
		EGG,

		//SmallCrow
		SCREAM,
		SCREAMMINI,
		
		//Death
		DEATHWHILERUNNING,

		DEATHWHILEUPRIGHT,
	};

	enum class Boss_OldCrowPattern //패턴 별
	{
		PATTERN1, // 대쉬, 대쉬
		PATTERN2, // 점프
		PATTERN3, // 사슬, 사슬, 점프, 대쉬
		PATTERN4, // 사슬, 사슬, 연속사슬, 점프, 대쉬
		PATTERN5, // SmallCrow 소환
		PATTERN6, // EGG 소환 
		PATTERNCOUNT //패턴 총 개수
	};

	//std::map<Boss_OldCrowState, BossStateParameter> StateMap;
	std::shared_ptr<class GameEngineFBXRenderer> BossRender = nullptr;
	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;

	void SetFSMFUNC();
	
};

