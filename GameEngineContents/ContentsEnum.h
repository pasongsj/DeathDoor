#pragma once

enum class OrderNum
{
	TEST
};


enum class PhysXFilterGroup //PhysX 충돌 용 그룹
{
	None = 0,
	PlayerDynamic = (1 << 0),		// 플레이어 충돌체		0000 0000 0000 0001
	Ground = (1 << 1),				// 바닥 충돌체			0000 0000 0000 0010
	Obstacle = (1 << 2),			// 장애물 충돌체		0000 0000 0000 0100
	GroundTrigger = (1 << 3),		// 트리거				0000 0000 0000 1000
	LeverTrigger = (1 << 4 ),	    // Frog_Lever			0000 0000 0001 0000
	PlayerSkill = (1 << 5),			//						0000 0000 0010 0000
	MonsterDynamic = (1 << 6),		//						0000 0000 0100 0000
	CullingTrigger = (1 << 7),       // test                0000 0000 1000 0000
	MonsterSkill = (1 << 8),		//						0000 0001 0000 0000
	JumperBoomer = (1 << 9),		//						0000 0010 0000 0000
	CrowDebuff = (1 << 10),		    // SmallCrow 패턴		0000 0100 0000 0000
};