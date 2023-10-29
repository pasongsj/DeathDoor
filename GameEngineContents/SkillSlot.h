#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Player.h"

class SkillSlot : public GameEngineActor
{

public:

	SkillSlot();
	~SkillSlot();

	SkillSlot(const SkillSlot& _Other) = delete;
	SkillSlot(SkillSlot&& _Other) noexcept = delete;
	SkillSlot& operator=(const SkillSlot& _Other) = delete;
	SkillSlot& operator=(SkillSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	Player::PlayerSkill CurSkill;
	Player::PlayerSkill PrevSkill;

	void SetSlot();
	bool LerpSlotScaleUp_Fire(float _DeltaTime);
	bool LerpSlotScaleDown_Fire(float _DeltaTime);

	bool LerpSlotScaleUp_Arrow(float _DeltaTime);
	bool LerpSlotScaleDown_Arrow(float _DeltaTime);

	bool LerpSlotScaleUp_Bomb(float _DeltaTime);
	bool LerpSlotScaleDown_Bomb(float _DeltaTime);

	bool LerpSlotScaleUp_Hook(float _DeltaTime);
	bool LerpSlotScaleDown_Hook(float _DeltaTime);

	void SkillChange();

	float LerpUpRatio = 0.0f;
	float LerpDownRatio = 0.0f;
	int CurSkillIndex = 0;

	std::list<std::function<bool(float)>> UpdateFunc;

	struct Slot
	{
		std::shared_ptr<class ContentUIRenderer> HalfSlot_1 = nullptr;
		std::shared_ptr<class ContentUIRenderer> HalfSlot_2 = nullptr;

		std::shared_ptr<class ContentUIRenderer> HalfSlotLinker_1 = nullptr;
		std::shared_ptr<class ContentUIRenderer> HalfSlotLinker_2 = nullptr;

		std::shared_ptr<class ContentUIRenderer> SkillRender = nullptr;

		float4 BasicPos_SkillRender = { 0, 0 };

		float4 BasicPos_Half_1 = { 0, 0 };

		float4 BasicScale_SkillRender = { 0, 0 };
	};

	std::vector<std::shared_ptr<Slot>> SlotList;
};

