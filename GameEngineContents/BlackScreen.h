#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BlackScreen : public GameEngineActor
{
public:
	// constrcuter destructer
	BlackScreen();
	~BlackScreen();

	// delete Function
	BlackScreen(const BlackScreen& _Other) = delete;
	BlackScreen(BlackScreen&& _Other) noexcept = delete;
	BlackScreen& operator=(const BlackScreen& _Other) = delete;
	BlackScreen& operator=(BlackScreen&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)override;
private:

	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
};

