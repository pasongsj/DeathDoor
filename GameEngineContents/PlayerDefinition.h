#pragma once
#include "PreCompileHeader.h"

#define PLAYER_SCALE_RATIO		6.0f
#define PLAYER_HIT_IDLE_TIME	3.0f
#define PLAYER_PHYSX_SCALE float4{0.0f, 150.0f, 90.0f}

#define PLAYER_ROLL_SPEED		1500.0f
#define PLAYER_CLIMB_SPEED		250.0f
#define PLAYER_MOVE_SPEED		500.0f
#define PLAYER_WALK_SPEED		150.0f

#define PLAYER_DEFAULT_DIR		float4::BACK

#define PLAYER_ATT_MOVE_SPEED	600.0f
#define PLAYER_ATT_BOX_PHYSX_SCALE		float4{200.0f, 1.0f, 200.0f}

#define PLAYER_ATT_MAGIC_PHYSX_SCALE	float4{50.0f, 50.0f, 50.0f}
#define PLAYER_ATT_MAGIC_RENDER_SCALE	float4{0.2f, 0.2f, 0.2f}


#define PLAYER_BOW_DEFAULT_DIR float4{0.0f ,-90.0f, 0.0f}
#define PLAYER_ATT_ARROW_PHYSX_SCALE	float4{0.0f, 100.0f, 10.0f}
#define PLAYER_ATT_ARROW_RENDER_SCALE	float4{0.2f, 0.2f, 0.2f}

#define PLAYER_ATT_BOMB_PHYSX_SCALE		float4{100.0f, 100.0f, 100.0f}
#define PLAYER_ATT_BOMB_RENDER_SCALE	float4{0.2f, 0.2f, 0.2f}
