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

	void SetFlickers()
	{
		Flickoption = true;
		FlickDuration = 5.0f;
		FlickInterval = 0.5f;

	}


protected:

	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineFBXRenderer> Renderer = nullptr;

	bool Flickoption = false;
	float FlickDuration = 5.0f;
	float FlickInterval = 0.5f;
};

