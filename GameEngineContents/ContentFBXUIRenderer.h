#pragma once
#include <GameEngineCore/GameEngineFBXRenderer.h>

class ContentFBXUIRenderer : public GameEngineFBXRenderer
{

public:

	ContentFBXUIRenderer();
	~ContentFBXUIRenderer();

	ContentFBXUIRenderer(const ContentFBXUIRenderer& _Other) = delete;
	ContentFBXUIRenderer(ContentFBXUIRenderer&& _Other) noexcept = delete;
	ContentFBXUIRenderer& operator=(const ContentFBXUIRenderer& _Other) = delete;
	ContentFBXUIRenderer& operator=(ContentFBXUIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

