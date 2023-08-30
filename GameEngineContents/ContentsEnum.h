#pragma once

enum class OrderNum
{
	TEST
};


enum class PhysXFilterGroup
{
	PlayerDynamic = (1 << 0),		// 플레이어 충돌체(HitCallback을 호출할 용도)
	Ground = (1 << 1),				// 바닥 충돌체(HitCallback을 호출할 용도)
	Obstacle = (1 << 2),			// 장애물 충돌체(HitCallback을 호출할 용도)
	GroundTrigger = (1 << 3),		// 땅 트리거 (보류)
};