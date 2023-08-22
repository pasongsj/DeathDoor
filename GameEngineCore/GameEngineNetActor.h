#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineNetObject.h>

// Ό³Έν :
class GameEngineNetActor : public GameEngineActor, public GameEngineNetObject
{
	friend class GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineNetActor();
	~GameEngineNetActor();

	// delete Function
	GameEngineNetActor(const GameEngineNetActor& _Other) = delete;
	GameEngineNetActor(GameEngineNetActor&& _Other) noexcept = delete;
	GameEngineNetActor& operator=(const GameEngineNetActor& _Other) = delete;
	GameEngineNetActor& operator=(GameEngineNetActor&& _Other) noexcept = delete;

protected:
	

private:

};

