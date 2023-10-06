#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "PhysXComponent.h"
// Ό³Έν :
class PlayerAttackBase : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	PlayerAttackBase();
	~PlayerAttackBase();

	// delete Function
	PlayerAttackBase(const PlayerAttackBase& _Other) = delete;
	PlayerAttackBase(PlayerAttackBase&& _Other) noexcept = delete;
	PlayerAttackBase& operator=(const PlayerAttackBase& _Other) = delete;
	PlayerAttackBase& operator=(PlayerAttackBase&& _Other) noexcept = delete;


protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class ContentFBXRenderer> AttackRenderer = nullptr;

	template<typename PhysXType>
	void CreatePhysXAttComp(const float4& _Scale)
	{
		PhysXComp = CreateComponent<PhysXType>();
		PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		PhysXComp->CreatePhysXActors(_Scale, float4::ZERO);
		PhysXComp->TurnOffGravity();
		PhysXComp->SetTrigger();
		PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill);
	}

	inline bool IsShoot()
	{
		return isShoot;
	}

private:
	bool isShoot = false;

	float4 Dir = float4::ZERO;
	float FireTime = 0.0f;

	void SetTrans(const float4& _Dir, const float4& _Pos);
	std::shared_ptr<class PhysXComponent> PhysXComp = nullptr;



	//void SetAttackType(AttackType _Type);

};

