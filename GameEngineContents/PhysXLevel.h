#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXCustom.h"

// Ό³Έν :
class PhysXLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PhysXLevel();
	virtual ~PhysXLevel() = 0;

	// delete Function
	PhysXLevel(const PhysXLevel& _Other) = delete;
	PhysXLevel(PhysXLevel&& _Other) noexcept = delete;
	PhysXLevel& operator=(const PhysXLevel& _Other) = delete;
	PhysXLevel& operator=(PhysXLevel&& _Other) noexcept = delete;

	//inline physx::PxScene* GetScene()
	//{
	//	return m_pScene;
	//}
	//
	//inline physx::PxPhysics* GetPhysics()
	//{
	//	return m_pPhysics;
	//}
	//
	//inline physx::PxCooking* GetCooking()
	//{
	//	return m_pCooking;
	//}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

};

