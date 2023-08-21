#pragma once
#include <GameEngineCore/GameEngineNetActor.h>

class GameContentsMapActor : public GameEngineNetActor
{
public:
	friend class MapEditorWindow;
	// constrcuter destructer
	GameContentsMapActor() ;
	~GameContentsMapActor();

	// delete Function
	GameContentsMapActor(const GameContentsMapActor& _Other) = delete;
	GameContentsMapActor(GameContentsMapActor&& _Other) noexcept = delete;
	GameContentsMapActor& operator=(const GameContentsMapActor& _Other) = delete;
	GameContentsMapActor& operator=(GameContentsMapActor&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class GameEngineFBXRenderer> Renderer = nullptr;
	
};

