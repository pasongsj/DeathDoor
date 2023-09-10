#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>


// Ό³Έν :
class MonsterBase : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterBase();
	~MonsterBase();

	// delete Function
	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

protected:

private:

	enum class MonsterState
	{
		IDLE,
		ROAM,
		AGGRO,
		ATTACK,
		MAX,
	};

	std::shared_ptr<class GameEngineFBXRenderer> MonsterRenderer = nullptr;
	//std::map<MonsterState, PlayerStateParameter> FSMFunc;



};

