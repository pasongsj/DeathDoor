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

	std::shared_ptr<class PhysXCapsuleComponent> GetPhysXComponent() const
	{
		return m_pCapsuleComp;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void UserUpdate(float _DeltaTime);
	void ServerUpdate(float _DeltaTime);

private:

	// Struct
	enum class PlayerState
	{
		IDLE,
		WALK,
		BASE_ATT,		// 좌클릭
		ROLL,			// 스페이스바
		SLIDE_ATT,		// 스페이스바+휠클릭
		CHARGE_ATT,		// 휠클릭
		SKILL,			// 우클릭
		ATTED,			// 공격당함
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
	void InitPlayer();
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
	bool isDown = false;

	float StateDuration = 2.0f;
	
	// input & move
	void CheckInput(float _DeltaTime);
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

