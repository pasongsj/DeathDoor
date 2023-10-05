#pragma once
#include <GameEngineContents/EnemyBase.h>

// Ό³Έν :
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
	virtual void InitAniamtion() {};
	virtual void InitPattern() {};

	std::shared_ptr<std::map<short, std::vector<short>>> Patterns = nullptr;

private:

};

