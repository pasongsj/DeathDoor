#include "PreCompileHeader.h"
#include "BossFrog.h"

#include "FrogBossLevel.h"
#include "Map_Sanctuary.h"

BossFrog* BossFrog::MainBoss;

BossFrog::BossFrog()
{
}

BossFrog::~BossFrog()
{
}
void BossFrog::Start()
{
	if (nullptr != MainBoss)
	{
		MainBoss->Death();
		MainBoss = nullptr;
	}
	MainBoss = this;
}

const float4 BossFrog::GetTilePos(const int _Y, const int _X)
{
	std::shared_ptr<FrogBossLevel> CurLevel = GetLevel()->DynamicThis<FrogBossLevel>();
	if (nullptr == CurLevel)
	{
		MsgAssert("Level 이 nullptr 입니다.");
	}

	float4 TilePos = CurLevel->GetMap()->GetTilePos(_Y, _X);

	return TilePos;
}

const float4 BossFrog::GetTileIndex(const float4& _Pos)
{
	std::shared_ptr<FrogBossLevel> CurLevel = GetLevel()->DynamicThis<FrogBossLevel>();
	if (nullptr == CurLevel)
	{
		MsgAssert("Level 이 nullptr 입니다.");
	}

	float4 TileIndex = CurLevel->GetMap()->GetTileIndex(_Pos);

	return TileIndex;
}

void BossFrog::FieldRotationStart()
{
	std::shared_ptr<FrogBossLevel> CurLevel = GetLevel()->DynamicThis<FrogBossLevel>();
	if (nullptr == CurLevel)
	{
		MsgAssert("Level 이 nullptr 입니다.");
	}

	CurLevel->GetMap()->OnRotationFloor();
}

void BossFrog::FieldRotationEnd()
{
	std::shared_ptr<FrogBossLevel> CurLevel = GetLevel()->DynamicThis<FrogBossLevel>();
	if (nullptr == CurLevel)
	{
		MsgAssert("Level 이 nullptr 입니다.");
	}

	CurLevel->GetMap()->OffRotationFloor();
}
