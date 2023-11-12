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


protected:
	void InitPattern() override;
	void SetFSMFUNC() override;
	void InitAnimation() override;
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class Boss_OldCrowState //스테이트 별
	{
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

		MAX,
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

	//체인 관련
	std::vector<std::shared_ptr<class Boss_OldCrowChain>> Chains;     //패턴에 사용되는 체인이 들어가있는 벡터
	std::vector<std::shared_ptr<class GameEngineActor>> ChainsPivots; //체인의 피봇 벡터
	std::vector<std::shared_ptr<class GameEngineComponent>> MegaDash2PatternTransforms1; //메가대쉬2 패턴에 사용될 트랜스폼1
	std::vector<std::shared_ptr<class GameEngineComponent>> MegaDash2PatternTransforms2; //메가대쉬2 패턴에 사용될 트랜스폼2
	std::shared_ptr<class GameEngineActor> MegaDash2PatternTransformPivot;

	//Init
	void ChainsInit();

	//랜덤패턴 구현
	void SetRandomPattern();    //랜덤한 패턴을 정해서 실행함
	void SetNextPatternState(); //정해진 랜덤한 패턴중 다음 패턴을 실행함

	//FSM 에서 사용되는 변수
	float4 Dir = float4::ZERO;  //목표 Dir
	float4 CurrentDir = float4::ZERO; //현재 Dir

	bool IsTurn = false; //회전 여부
	bool IsDeath = false;

	float CurrentChainSpeed = 10.0f;
	float StateCalTime = 0.0f;
	float StateCalTime2 = 0.0f;
	float StateCalFloat = 0.0f;
	float4 TargetPos = float4::ZERO;
	float4 StartPos = float4::ZERO;
	float4 JumpDir = float4::ZERO;
	float4 SlamDir = float4::ZERO;
	int MegaDash2PatternCount = 0;
	int MegaDash2PatternNumber = 0;  
	float CurrentSpeed = 0.0f;
	bool StateCalBool = false;

	//FSM에서 사용되는 함수
	void TurnCheck(); //대쉬 중 회전 스테이트로 변경할 것인지 체크
	void SetLerpDirection(float _DeltaTime); //러프로 회전하는 (대쉬, 턴) 스테이트에서 사용
	void SetDirection(); //즉시 Dir로 회전
	void SettingChainPatternPivot(); //연속 사슬 패턴 이전에 사용할 Pivot을 조정함
	void SetMegaDashRandomPos(); //랜덤한 위치로 텔레포트하는 메가대쉬 패턴 시

	float4 GetRandomPos(float _Value);

	void GetDamaged();		//피격 체크
	float DamagedTime = 0.0f; //특정 시간동안 데미지 받지 않게끔 

	void SetDeathState();

	void CreateCrowHead();

	//Particle
	void CreateFeatherParticle();
	float FeatherCount = 0.0f;

	void CreateDustParticle();
	float DustCount = 0.0f;

	float4 StartColor = { 0.956f, 0.286f, 0.372f };
	float4 EndColor = { 0.0f, 0.0f, 0.0f };
	float LerpRatio = 0.0f;
};

