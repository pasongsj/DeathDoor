#pragma once
#define PLAYER_JUMP_FORCE 100.f
#define PLAYER_MAX_SPEED 400.f
#define SCENE_GRAVITY 981.f


class GlobalValue
{
public:
	static std::set<std::pair<UINT, UINT>> PhysXCollision;
};

