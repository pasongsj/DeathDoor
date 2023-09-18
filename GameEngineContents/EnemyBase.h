#pragma once
#include "FSMObjectBase.h"
#include "EnemyDefinition.h"
#include "PhysXCapsuleComponent.h"

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
	std::shared_ptr<class GameEngineFBXRenderer> EnemyRenderer = nullptr;

	virtual void InitAniamtion() {};
	void Start() override;
	void Update(float _DetltaTime) override;

	bool InRangePlayer(float _Range);

	float4 GetPlayerDir();

	float4 AggroDir(std::shared_ptr<class PhysXCapsuleComponent> _Comp, float4 DefaultDir = float4::ZERO);
private:


	

};

