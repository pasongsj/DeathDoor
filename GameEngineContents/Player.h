#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineNetObject.h>



// 설명 :
class Player : public GameEngineActor, public GameEngineNetObject
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void UserUpdate(float _DeltaTime);
	void ServerUpdate(float _DeltaTime);

private:

	// Struct
	enum class PlayerState
	{
		IDLE,			// Idle_0, Idle_1
		TURN,			// Cutscene_turn_half, Cutscene_turn_stopped, Cutscene_turn_end
		WALK,			// Walk, Run
		SKILL,			// 우클릭 Arrow, Arrow_bomb, Arrow_magic, Hookshot, Hookshot_fly
		HOOK_FLY,		// Hookshot_fly
		BASE_ATT,		// 좌클릭 Slash_Light_L_new, Slash_Light_R_new
		ROLL,			// 스페이스바 Roll, Roll_slash
		ROLL_ATT,		// 스페이스바+휠클릭 Charge_slam_overhead, Roll_slash_end
		CHARGE_ATT,		// 휠클릭 Charge_slash_L, Charge_slash_R
		HIT,			// 공격당함 Hit_back, Hit_idle,Hit_Recover
		CLIMB,			// 사다리 Climbing_ladder, Climbing_ladder_down, Climbing_off_ladder_top
		LEVER,			// 레버를 누름 Push_Lever
		ITEM,			// 아이템을 얻음 GetItem
		DEAD,			// 피격으로 인한 사망 Dead
		DROWN,			// 익사 Drown
		FALLING,		// 낙사 Falling
		FLY,			// 높이가 차가 있을 때 FLy, Land
		MAX,
	};

	enum class PlayerSkill
	{
		ARROW,
		FIRE,
		BOMB,
		HOOK,
		MAX,
	};

	class PlayerStateParameter
	{
	public:
		std::function<void()> Start = nullptr;
		std::function<void(float _Delta)> Update = nullptr;
		std::function<void()> End = nullptr;
	};



	// Init
	std::atomic_int AnimationLoadCount = 0;
	void InitInputKey();
	void InitPlayerAnimatioin();
	std::map<PlayerState, PlayerStateParameter> FSMFunc;
	void SetFSMFunc();

	// Render
	std::shared_ptr<GameEngineFBXRenderer> Renderer = nullptr;


	// State
	PlayerState CurState = PlayerState::MAX;
	PlayerState NextState = PlayerState::IDLE;
	void UpdateState(float _DeltaTime);
		// Attack
	PlayerSkill CurSkill = PlayerSkill::ARROW;
	bool isRightAttack = true;

	float StateDuration = 2.0f;
	bool StateChecker = false;
	
	// input & move
	void CheckInput(float _DeltaTime);
	void CheckClimbInput(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);

	float4 MoveDir = float4::ZERO;
	float4 PrevDir = float4::ZERO;
	float MoveSpeed;
	bool mButton = false;


	//physx
	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;


	// for test
	std::vector<std::string> AnimationName;
	void TestInit();
	int index = 0;
	float m_pSpeed = 200.0f;
	void TestMoveUpdate(float _DeltaTime);
};

