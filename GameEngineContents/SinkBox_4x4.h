#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SinkBox_4x4 : public GameEngineActor
{

public:

	SinkBox_4x4();
	~SinkBox_4x4();

	SinkBox_4x4(const SinkBox_4x4& _Other) = delete;
	SinkBox_4x4(SinkBox_4x4&& _Other) noexcept = delete;
	SinkBox_4x4& operator=(const SinkBox_4x4& _Other) = delete;
	SinkBox_4x4& operator=(SinkBox_4x4&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

