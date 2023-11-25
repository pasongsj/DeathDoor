#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class PlayerInfoWindow : public GameEngineGUIWindow
{
public:
	static PlayerInfoWindow* PlayerGUI;
	// constrcuter destructer
	PlayerInfoWindow();
	~PlayerInfoWindow();

	// delete Function
	PlayerInfoWindow(const PlayerInfoWindow& _Other) = delete;
	PlayerInfoWindow(PlayerInfoWindow&& _Other) noexcept = delete;
	PlayerInfoWindow& operator=(const PlayerInfoWindow& _Other) = delete;
	PlayerInfoWindow& operator=(PlayerInfoWindow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:

};

