#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"

Boss_OldCrow::Boss_OldCrow() 
{

}

Boss_OldCrow::~Boss_OldCrow() 
{

}

void Boss_OldCrow::Init()
{
	EnemyBaseInit("OldCrowTest.fbx", 1000.0f);
	AnimationInit();
	StateMachineInit();
}

void Boss_OldCrow::Start()
{
	Init();
}