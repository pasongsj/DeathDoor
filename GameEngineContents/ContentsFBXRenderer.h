#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class ContentsFBXRenderer : public GameEngineFBXRenderer
{
public:
	// constrcuter destructer
	ContentsFBXRenderer() ;
	~ContentsFBXRenderer();

	// delete Function
	ContentsFBXRenderer(const ContentsFBXRenderer& _Other) = delete;
	ContentsFBXRenderer(ContentsFBXRenderer&& _Other) noexcept = delete;
	ContentsFBXRenderer& operator=(const ContentsFBXRenderer& _Other) = delete;
	ContentsFBXRenderer& operator=(ContentsFBXRenderer&& _Other) noexcept = delete;
	
	inline bool GetIsMoveableActor()
	{
		return IsMoveableActor;
	}

protected:

private:

	bool IsMoveableActor = false;

};

