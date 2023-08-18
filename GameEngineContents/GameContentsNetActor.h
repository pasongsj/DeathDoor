#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineNetObject.h>

class GameContentsNetActor : public GameEngineActor, public GameEngineNetObject
{
public:
	// constrcuter destructer
	GameContentsNetActor() ;
	~GameContentsNetActor();

	// delete Function
	GameContentsNetActor(const GameContentsNetActor& _Other) = delete;
	GameContentsNetActor(GameContentsNetActor&& _Other) noexcept = delete;
	GameContentsNetActor& operator=(const GameContentsNetActor& _Other) = delete;
	GameContentsNetActor& operator=(GameContentsNetActor&& _Other) noexcept = delete;

protected:

private:

};

