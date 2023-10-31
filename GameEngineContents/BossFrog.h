#pragma once
#include "EnemyBase.h"
#include "Player.h"

class BossFrog : public EnemyBase
{
public:
	static BossFrog* MainBoss;
	// constrcuter destructer
	BossFrog() ;
	~BossFrog();

	// delete Function
	BossFrog(const BossFrog& _Other) = delete;
	BossFrog(BossFrog&& _Other) noexcept = delete;
	BossFrog& operator=(const BossFrog& _Other) = delete;
	BossFrog& operator=(BossFrog&& _Other) noexcept = delete;

protected:
	void Start() override;

	// 타일
	const float4 GetTilePos(const int _Y, const int _X);
	const float4 GetTileIndex(const float4& _Pos);
	
	void DestroyTile(const int _Y, const int _X);
	void ShakeTile(const int _Y, const int _X, float _ShakeTime);
	bool IsTile(const int _Y, const int _X);
	void AllTileReset();

	// 보스 필드
	void FieldRotationStart();
	void FieldRotationEnd();

	// 보스
	float4 GetWaterPoint();
	const float4 UnderWaterCenter = float4{ -3634.12842f, -723.0f ,3618.32715f };
	const float4 OnGroundCenter = float4{ -3634.12842f, -180.0f ,3618.32715f };

	const float4 WPointWest = float4{ -4815,-730,2620 };
	const float4 WPointEast = float4{ -2475,-730,4740 };
	const float4 WPointNorth = float4{ -4790,-730,4800 };
	const float4 WPointSouth = float4{ -2400,-730,2450 };

private:
	void SetLevel();
	std::weak_ptr<class FrogBossLevel> m_pCurLevel;
	
};

