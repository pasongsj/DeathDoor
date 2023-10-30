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
	SetLevel();
}

const float4 BossFrog::GetTilePos(const int _Y, const int _X)
{
	float4 TilePos = m_pCurLevel.lock()->GetMap().lock()->GetTilePos(_Y, _X);

	return TilePos;
}

const float4 BossFrog::GetTileIndex(const float4& _Pos)
{
	float4 TileIndex = m_pCurLevel.lock()->GetMap().lock()->GetTileIndex(_Pos);

	return TileIndex;
}

void BossFrog::DestroyTile(const int _Y, const int _X)
{
	m_pCurLevel.lock()->GetMap().lock()->DestroyTile(_Y, _X);
}

bool BossFrog::IsTile(const int _Y, const int _X)
{
	return  m_pCurLevel.lock()->GetMap().lock()->IsTile(_Y, _X);
}

void BossFrog::ResetTile()
{
	m_pCurLevel.lock()->GetMap().lock()->ResetTile();
}

void BossFrog::FieldRotationStart()
{
	m_pCurLevel.lock()->GetMap().lock()->OnRotationFloor();
}

void BossFrog::FieldRotationEnd()
{
	m_pCurLevel.lock()->GetMap().lock()->OffRotationFloor();
}

void BossFrog::SetLevel()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr != CurLevel)
	{
		m_pCurLevel = CurLevel->DynamicThis<FrogBossLevel>();
	}
}
