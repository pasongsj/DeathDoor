#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class SelectLevel : public GameEngineLevel
{

public:

	SelectLevel();
	~SelectLevel();

	SelectLevel(const SelectLevel& _Other) = delete;
	SelectLevel(SelectLevel&& _Other) noexcept = delete;
	SelectLevel& operator=(const SelectLevel& _Other) = delete;
	SelectLevel& operator=(SelectLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class CharacterList> Level_CharacterList = nullptr;
};

