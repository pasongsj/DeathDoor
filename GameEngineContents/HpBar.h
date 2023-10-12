#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HpBar : public GameEngineActor
{

public:

	HpBar();
	~HpBar();

	HpBar(const HpBar& _Other) = delete;
	HpBar(HpBar&& _Other) noexcept = delete;
	HpBar& operator=(const HpBar& _Other) = delete;
	HpBar& operator=(HpBar&& _Other) noexcept = delete;

	void ReduceHp();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	void HpUpdate();

	int MaxHp = 4;
	int CurHp = 4;
	int PrevHp = 4;

	std::shared_ptr<class ContentUIRenderer> HpBarRender = nullptr;
	std::vector<std::shared_ptr<ContentUIRenderer>> HpBlocks;

};

