#pragma once
#include <GameEngineContents/EnemyBase.h>

// 설명 :
class BossBase : public EnemyBase
{
public:
	// constrcuter destructer
	BossBase();
	~BossBase();

	// delete Function
	BossBase(const BossBase& _Other) = delete;
	BossBase(BossBase&& _Other) noexcept = delete;
	BossBase& operator=(const BossBase& _Other) = delete;
	BossBase& operator=(BossBase&& _Other) noexcept = delete;

protected:
	//virtual void InitAniamtion() {};
	virtual void InitPattern() {};

	std::map<short, std::vector<short>> Patterns;

	short PatternNum = 0; //현재 진행중인 패턴 번호
	short CurrentPatternNum = 0; //패턴 번호의 몇번째 패턴 진행중인지

private:

};

