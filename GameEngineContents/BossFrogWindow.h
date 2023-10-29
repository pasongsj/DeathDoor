#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class BossFrogWindow : public GameEngineGUIWindow
{
public:
	static BossFrogWindow* EditorGUI;

	// constrcuter destructer
	BossFrogWindow();
	~BossFrogWindow();

	// delete Function
	BossFrogWindow(const BossFrogWindow& _Other) = delete;
	BossFrogWindow(BossFrogWindow&& _Other) noexcept = delete;
	BossFrogWindow& operator=(const BossFrogWindow& _Other) = delete;
	BossFrogWindow& operator=(BossFrogWindow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:

};

