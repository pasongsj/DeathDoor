#pragma once
#include "EnemyBase.h"

// Ό³Έν :
class BossFrog : public EnemyBase
{
public:
	// constrcuter destructer
	BossFrog();
	~BossFrog();

	// delete Function
	BossFrog(const BossFrog& _Other) = delete;
	BossFrog(BossFrog&& _Other) noexcept = delete;
	BossFrog& operator=(const BossFrog& _Other) = delete;
	BossFrog& operator=(BossFrog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void InitAniamtion() override;

private:

};

