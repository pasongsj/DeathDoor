#pragma once
#include "FSMObjectBase.h"
#include "EnemyDefinition.h"

// Ό³Έν :
class EnemyBase : public FSMObjectBase
{
public:
	// constrcuter destructer
	EnemyBase();
	~EnemyBase();

	// delete Function
	EnemyBase(const EnemyBase& _Other) = delete;
	EnemyBase(EnemyBase&& _Other) noexcept = delete;
	EnemyBase& operator=(const EnemyBase& _Other) = delete;
	EnemyBase& operator=(EnemyBase&& _Other) noexcept = delete;

protected:

	virtual void InitAniamtion() {};
	void Start() override;
	void Update(float _DetltaTime) override;


private:
	

};

