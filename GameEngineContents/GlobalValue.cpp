#include "PreCompileHeader.h"
#include "GlobalValue.h"

std::set<std::pair<UINT, UINT>> GlobalValue::PhysXCollision =
{ 
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerSkill), static_cast<UINT>(PhysXFilterGroup::MonsterDynamic)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerDynamic), static_cast<UINT>(PhysXFilterGroup::MonsterSkill)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerSkill), static_cast<UINT>(PhysXFilterGroup::Obstacle)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerDynamic), static_cast<UINT>(PhysXFilterGroup::CullingTrigger)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::MonsterSkill), static_cast<UINT>(PhysXFilterGroup::JumperBoomer)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerDynamic), static_cast<UINT>(PhysXFilterGroup::LeverTrigger)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerSkill), static_cast<UINT>(PhysXFilterGroup::LeverTrigger)),
	std::make_pair(static_cast<UINT>(PhysXFilterGroup::CrowDebuff), static_cast<UINT>(PhysXFilterGroup::PlayerDynamic)),
};
