#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SinkBox_8x8 : public GameEngineActor
{

public:

	SinkBox_8x8();
	~SinkBox_8x8();

	SinkBox_8x8(const SinkBox_8x8& _Other) = delete;
	SinkBox_8x8(SinkBox_8x8&& _Other) noexcept = delete;
	SinkBox_8x8& operator=(const SinkBox_8x8& _Other) = delete;
	SinkBox_8x8& operator=(SinkBox_8x8&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

