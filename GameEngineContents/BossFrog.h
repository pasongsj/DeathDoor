#pragma once
#include "EnemyBase.h"

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
	bool IsTile(const int _Y, const int _X);
	void ResetTile();

	// 보스 필드
	void FieldRotationStart();
	void FieldRotationEnd();

private:
	void SetLevel();
	std::shared_ptr<class FrogBossLevel> m_pCurLevel = nullptr;
	
};

