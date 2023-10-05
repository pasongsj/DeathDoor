#include "PrecompileHeader.h"

std::set<std::pair<UINT, UINT>> GlobalValue::PhysXCollision = { std::make_pair(static_cast<UINT>(PhysXFilterGroup::PlayerSkill), static_cast<UINT>(PhysXFilterGroup::MonsterDynamic)), };
