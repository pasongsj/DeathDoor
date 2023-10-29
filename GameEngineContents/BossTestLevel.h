#pragma once
#include "ContentLevel.h"

// 설명 : 보스 테스트용 레벨
class BossTestLevel : public ContentLevel
{
public:
	// constrcuter destructer
	BossTestLevel();
	~BossTestLevel();

	// delete Function
	BossTestLevel(const BossTestLevel& _Other) = delete;
	BossTestLevel(BossTestLevel&& _Other) noexcept = delete;
	BossTestLevel& operator=(const BossTestLevel& _Other) = delete;
	BossTestLevel& operator=(BossTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;


private:

};

