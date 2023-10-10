#pragma once
#include <GameEngineContents/BossBase.h>
#include "Boss_OldCrowDefinition.cpp"


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

	std::shared_ptr<class PhysXCapsuleComponent> GetPhysXComponent()
	{
		return m_pCapsuleComp;
	}

protected:
	void InitAniamtion() override;
	void InitPattern() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class Boss_OldCrowState //스테이트 별
	{
		EMPTY,

		IDLE,

		//대쉬
		DASHSTART,
		DASH,
		TURN,

		//사슬
		MEGADASHPREP,
		MEGADASHPREPRANDOMPOS,
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
		PATTERNCOUNT //패턴 총 개수 (size)
	};


	class ChainPatternParameter
	{
	public:
		float4 StartPos = float4::ZERO;
		float4 Dir = float4::ZERO;
	};

	std::shared_ptr<class ContentFBXRenderer> BossRender = nullptr;
	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;

	//체인 관련
	std::vector<std::shared_ptr<class Boss_OldCrowChain>> Chains;
	std::vector<std::shared_ptr<class GameEngineComponent>> ChainsPivots;
	std::shared_ptr<Boss_OldCrowChain> GetChain();

	//Init
	void ChainsInit();

	//랜덤패턴 구현
	void SetRandomPattern();    //랜덤한 패턴을 정해서 실행함
	void SetNextPatternState(); //정해진 랜덤한 패턴중 다음 패턴을 실행함

	//FSM Init
	void SetFSMFUNC();

	//FSM 에서 사용되는 변수
	float4 Dir = float4::ZERO;  //목표 Dir
	float4 CurrentDir = float4::ZERO; //현재 Dir

	bool IsTurn = false; //회전 여부
	std::vector<std::vector<int>> UsingChainNumber; //사용중인 체인 번호 벡터
	std::vector<class ChainPatternParameter> ChainPatternParameterVector;

	float CurrentChainSpeed = 0.0f;
	float StateCalTime = 0.0f;
	float StateCalTime2 = 0.0f;
	float4 TargetPos = float4::ZERO;
	float4 JumpForce = float4::ZERO;

	// FSM 에서 사용되는 상수
	const float DashSpeed = 1000.0f;
	const float DashSpeed2 = DashSpeed * 0.75f;
	const float MegaDashSpeed = 5000.0f;
	const int ChainsCount = 10;
	const float ChainSpeed = 100.0f;
	const float CreateChainTime = 1.5f;
	const int ChainPivotCount = 4;

	//FSM에서 사용되는 함수
	void TurnCheck(); //대쉬 중 회전 스테이트로 변경할 것인지 체크
	void SetLerpDirection(float _DeltaTime); //러프로 회전하는 (대쉬, 턴) 스테이트에서 사용
	void SetDirection(); //즉시 Dir로 회전
	void SettingChainPatternParameter(); //연속 사슬 패턴 이전에 사용할 Pivot, Dir등을 세팅

	float4 GetRandomPos(float _Value);
};

