#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "PhysXComponent.h"
#include "PlayerAttackDefinition.h"
#include "EnemyDefinition.h"

// 설명 :
class AttackBase : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	AttackBase();
	~AttackBase();

	// delete Function
	AttackBase(const AttackBase& _Other) = delete;
	AttackBase(AttackBase&& _Other) noexcept = delete;
	AttackBase& operator=(const AttackBase& _Other) = delete;
	AttackBase& operator=(AttackBase&& _Other) noexcept = delete;


	void SetTrans(const float4& _Dir, const float4& _Pos = float4::ZERONULL);

	std::shared_ptr<class PhysXComponent> GetPhysXComponent()
	{
		return PhysXComp;
	}

	std::shared_ptr<class ContentFBXRenderer> GetRenderer()
	{
		return AttackRenderer;
	}
	

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class ContentFBXRenderer> AttackRenderer = nullptr;
	std::shared_ptr<class PhysXComponent> PhysXComp = nullptr;


	template<typename PhysXType>
	void CreatePhysXAttComp(const float4& _Scale, PhysXFilterGroup _Group)
	{
		if (nullptr != PhysXComp)
		{
			MsgAssert("이미 생성된 컴퍼넌트 입니다");
			return;
		}
		PhysXComp = CreateComponent<PhysXType>();
		PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		PhysXComp->CreatePhysXActors(_Scale, float4::ZERO);
		PhysXComp->TurnOffGravity();
		PhysXComp->SetTrigger();
		PhysXComp->SetFilterData(_Group);
	}

	inline bool IsShoot()
	{
		return isShoot;
	}

	virtual void SetShoot(float _Speed = 1500.0f)
	{
		SetShootSpeed(_Speed);
		ResetLiveTime();
		isShoot = true;
	}

	inline void SetShootSpeed(float _Speed)
	{
		ShootSpeed = _Speed;
	}

	inline float GetSootSpeed()
	{
		return ShootSpeed;
	}

	inline void SetDestTarget(PhysXFilterGroup Tar)
	{
		DestTarget = Tar;
	}

	virtual void CreateParticle(float _DeltaTime) {}

	float4 GetDir() const
	{
		return Dir;
	}

	float GetShootSpeed() const
	{
		return ShootSpeed;
	}

private:
	bool isShoot = false;

	float4 Dir = float4::ZERO;
	float FireTime = 0.0f;

	float ShootSpeed = 1500.0f;

	PhysXFilterGroup DestTarget = PhysXFilterGroup::None;
};

