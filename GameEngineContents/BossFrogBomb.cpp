#include "PrecompileHeader.h"
#include "BossFrogBomb.h"
#include "TileManager.h"

BossFrogBomb::BossFrogBomb()
{
}

BossFrogBomb::~BossFrogBomb()
{
}
void BossFrogBomb::SetTargetTile(const float4& _Start, const float4& _Target)
{
	if (_Target == float4::ZERONULL)
	{
		Death();
		return;
	}
	TileManager::MainManager->InActiveTile(_Target.iy(), _Target.ix());
	Startpoint = _Start;
	Target = TileManager::MainManager->GetTilePos(_Target.iy(), _Target.ix());
	ResetLiveTime();
	P2 = Startpoint * 0.5f + Target * 0.5f;
	P2.y += 800.0f;
}
void BossFrogBomb::Start()
{
	BombRender = CreateComponent<ContentFBXRenderer>();
	BombRender->SetFBXMesh("SplashImpact_Big.fbx", "ContentMeshDeffered");
	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
}

void BossFrogBomb::Update(float _DeltaTime)
{
	if (true == Target.IsZero())
	{
		return;
	}
	if (GetLiveTime() > 1.5f || Target == float4::ZERONULL)
	{
		Death();
		if (Target == float4::ZERONULL)
		{
			return;
		}
		float4 index = TileManager::MainManager->GetTileIndex(Target);
		TileManager::MainManager->DestroyTile(index.iy(), index.ix());
		// 타일 삭제하기
	}
	GetTransform()->SetWorldPosition(float4::Bazier3LerpClamp(Startpoint, P2, Target, GetLiveTime() * 0.66666f));
}
