#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class CenterGui : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	CenterGui();
	~CenterGui();

	// delete Function
	CenterGui(const CenterGui& _Other) = delete;
	CenterGui(CenterGui&& _Other) noexcept = delete;
	CenterGui& operator=(const CenterGui& _Other) = delete;
	CenterGui& operator=(CenterGui&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) override;

private:

};

