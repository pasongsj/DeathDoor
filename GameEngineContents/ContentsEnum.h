#pragma once

enum class OrderNum
{
	TEST
};


enum class PhysXFilterGroup //PhysX 충돌 용 그룹
{
	None = 0,
	PlayerDynamic = (1 << 0),		// 플레이어 충돌체
	Ground = (1 << 1),				// 바닥 충돌체
	Obstacle = (1 << 2),			// 장애물 충돌체
	GroundTrigger = (1 << 3),		// 트리거

	LeverTrigger = (1 << 4 ),	    // Frog_Lever
};