#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ParticleCreater : public GameEngineActor
{

public:

	ParticleCreater();
	~ParticleCreater();

	ParticleCreater(const ParticleCreater& _Other) = delete;
	ParticleCreater(ParticleCreater&& _Other) noexcept = delete;
	ParticleCreater& operator=(const ParticleCreater& _Other) = delete;
	ParticleCreater& operator=(ParticleCreater&& _Other) noexcept = delete;

protected:

private:

};

