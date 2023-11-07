#pragma once
#include "FSMObjectBase.h"
#include "EnemyDefinition.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"

// ¼³¸í :
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

	std::shared_ptr<class PhysXControllerComponent> GetPhysXComponent() const
	{
		return m_pCapsuleComp;
	}

	void SetSpawnPoint(const float4& _SpawnPoint)
	{
		SpawnPoint = _SpawnPoint;
		MoveToSpawnPoint();
	}

protected:
	std::shared_ptr<class ContentFBXRenderer> EnemyRenderer = nullptr;
	std::shared_ptr<class PhysXControllerComponent> m_pCapsuleComp = nullptr;

	virtual void InitAnimation() {};
	virtual void SetFSMFUNC() {};

	void Start() override;
	void Update(float _DetltaTime) override;

	bool InRangePlayer(float _Range);

	float4 GetPlayerPosition();

	float4 GetPlayerDir();

	float4 AggroDir(std::shared_ptr<class PhysXControllerComponent> _Comp, float4 DefaultDir = float4::ZERO);

	float4 GetRotationDegree(const float4& _CurDir);

	virtual bool CheckHit();

	bool DeathCheck();

	void AddPlayerSpellCost();

	void SetEnemyHP(int _HP)
	{
		m_TotalHP = m_iEnemyHP = _HP;
	}

	int GetEnemyHP() const
	{
		return m_iEnemyHP;
	}

	void MoveToSpawnPoint()
	{
		if (nullptr == m_pCapsuleComp)
		{
			GetTransform()->SetLocalPosition(SpawnPoint);
		}
		else
		{
			m_pCapsuleComp->SetWorldPosWithParent(SpawnPoint);
		}
	}
private:
	int m_iEnemyHP = -1;// ÇöÀçHP
	int m_TotalHP = -1; //ÃÑHP
	
	float4 SpawnPoint = float4::ZERONULL;

};

