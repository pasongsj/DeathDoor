#include "PreCompileHeader.h"
#include "BossFrog.h"

#include "FrogBossLevel.h"
#include "Map_Sanctuary.h"

#include "TileManager.h"

BossFrog* BossFrog::MainBoss;

BossFrog::BossFrog()
{
}

BossFrog::~BossFrog()
{
}
void BossFrog::Start()
{
	//if (nullptr != MainBoss)
	//{
	//	MainBoss->Death();
	//	MainBoss = nullptr;
	//}

	MainBoss = this;
}

const float4 BossFrog::GetTilePos(const int _Y, const int _X)
{
	float4 TilePos = TileManager::MainManager->GetTilePos(_Y, _X);

	return TilePos;
}

void BossFrog::InActiveTile(const int _Y, const int _X)
{
	TileManager::MainManager->InActiveTile(_Y, _X);
}

const float4 BossFrog::GetTileIndex(const float4& _Pos)
{
	float4 TileIndex = TileManager::MainManager->GetTileIndex(_Pos);

	return TileIndex;
}

void BossFrog::DestroyTile(const int _Y, const int _X)
{
	TileManager::MainManager->DestroyTile(_Y, _X);
}

void BossFrog::ShakeTile(const int _Y, const int _X, float _ShakeTime)
{
	TileManager::MainManager->ShakeTile(_Y, _X, _ShakeTime);
}

bool BossFrog::IsTile(const int _Y, const int _X)
{
	return TileManager::MainManager->IsTile(_Y, _X);
}

void BossFrog::AllTileReset()
{
	TileManager::MainManager->ResetTile();
}

void BossFrog::FieldRotationStart()
{
	TileManager::MainManager->OnRotation();
}

void BossFrog::FieldRotationEnd()
{
	TileManager::MainManager->OffRotation();
}

float4 BossFrog::GetWaterPoint()
{
	float4 ForwardVec = GetTransform()->GetWorldForwardVector();
	if (ForwardVec.x < 0)
	{
		if (ForwardVec.z < 0)
		{
			//west
			return WPointWest;
		}
		else
		{
			//north
			return WPointNorth;
		}
	}
	else
	{
		if (ForwardVec.z < 0)
		{
			//south
			return WPointSouth;
		}
		else
		{
			//east
			return WPointEast;
		}

	}
}
