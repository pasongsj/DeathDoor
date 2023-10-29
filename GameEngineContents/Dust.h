#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Dust : public GameEngineActor
{

public:

	Dust();
	~Dust();

	Dust(const Dust& _Other) = delete;
	Dust(Dust&& _Other) noexcept = delete;
	Dust& operator=(const Dust& _Other) = delete;
	Dust& operator=(Dust&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class DustRenderer> Dust1 = nullptr;
	std::shared_ptr<class DustRenderer> Dust2 = nullptr;
	std::shared_ptr<class DustRenderer> Dust3 = nullptr;
	std::shared_ptr<class DustRenderer> Dust4 = nullptr;

};

