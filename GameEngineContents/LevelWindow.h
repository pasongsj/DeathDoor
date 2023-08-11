#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class LevelWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	LevelWindow();
	~LevelWindow();

	// delete Function
	LevelWindow(const LevelWindow& _Other) = delete;
	LevelWindow(LevelWindow&& _Other) noexcept = delete;
	LevelWindow& operator=(const LevelWindow& _Other) = delete;
	LevelWindow& operator=(LevelWindow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:
	std::string m_CurLevelName = "CenterLevel";

	std::string m_CurCameraMode = "Play Mode";
};

