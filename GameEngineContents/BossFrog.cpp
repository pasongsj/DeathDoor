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
	m_pCurLevel = nullptr;
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
	float4 TilePos = m_pCurLevel->GetMap()->GetTilePos(_Y, _X);

	return TilePos;
}

const float4 BossFrog::GetTileIndex(const float4& _Pos)
{
	float4 TileIndex = m_pCurLevel->GetMap()->GetTileIndex(_Pos);

	return TileIndex;
}

void BossFrog::DestroyTile(const int _Y, const int _X)
{
	m_pCurLevel->GetMap()->DestroyTile(_Y, _X);
}

bool BossFrog::IsTile(const int _Y, const int _X)
{
	return m_pCurLevel->GetMap()->IsTile(_Y, _X);
}

void BossFrog::ResetTile()
{
	m_pCurLevel->GetMap()->ResetTile();
}

void BossFrog::FieldRotationStart()
{
	m_pCurLevel->GetMap()->OnRotationFloor();
}

void BossFrog::FieldRotationEnd()
{
	m_pCurLevel->GetMap()->OffRotationFloor();
}

void BossFrog::SetLevel()
{
	if (nullptr == m_pCurLevel)
	{
		m_pCurLevel = GetLevel()->DynamicThis<FrogBossLevel>().get();
	}
}
