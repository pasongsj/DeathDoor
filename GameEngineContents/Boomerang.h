#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Boomerang : public GameEngineActor
{

public:

	Boomerang();
	~Boomerang();

	Boomerang(const Boomerang& _Other) = delete;
	Boomerang(Boomerang&& _Other) noexcept = delete;
	Boomerang& operator=(const Boomerang& _Other) = delete;
	Boomerang& operator=(Boomerang&& _Other) noexcept = delete;

protected:

private:

};

