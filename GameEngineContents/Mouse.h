#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Mouse : public GameEngineActor
{

public:

	Mouse();
	~Mouse();

	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void MouseOnOff();

	void MouseRotationUpdate();
	void RayCasting();
	int Count = 0;

	bool isCursorOn = false;

	std::shared_ptr<class GameEngineComponent> MousePivot = nullptr;
	std::shared_ptr<class ContentFBXUIRenderer> MouseCursor = nullptr;

	std::shared_ptr<class GameEngineCollision> Ray = nullptr;
};

