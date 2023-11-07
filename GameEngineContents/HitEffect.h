#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HitEffect : public GameEngineActor
{

public:

	HitEffect();
	~HitEffect();

	HitEffect(const HitEffect& _Other) = delete;
	HitEffect(HitEffect&& _Other) noexcept = delete;
	HitEffect& operator=(const HitEffect& _Other) = delete;
	HitEffect& operator=(HitEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	void BillBoarding();

};

