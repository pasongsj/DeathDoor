#pragma once
#include "ContentLevel.h"

class StartLevel : public ContentLevel
{

public:

	StartLevel();
	~StartLevel();

	StartLevel(const StartLevel& _Other) = delete;
	StartLevel(StartLevel&& _Other) noexcept = delete;
	StartLevel& operator=(const StartLevel& _Other) = delete;
	StartLevel& operator=(StartLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

};

