#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PhysXActor.h"

// Ό³Έν :
class Map_PhysXActor : public GameEngineActor , public PhysXActor
{
public:
	// constrcuter destructer
	Map_PhysXActor();
	~Map_PhysXActor();

	// delete Function
	Map_PhysXActor(const Map_PhysXActor& _Other) = delete;
	Map_PhysXActor(Map_PhysXActor&& _Other) noexcept = delete;
	Map_PhysXActor& operator=(const Map_PhysXActor& _Other) = delete;
	Map_PhysXActor& operator=(Map_PhysXActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void CreatePhysXComponent() override;

private:
	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;
};
