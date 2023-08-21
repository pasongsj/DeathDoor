#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PhysXTestActor :public GameEngineActor 
{
public:
	// constrcuter destructer
	PhysXTestActor();
	~PhysXTestActor();

	// delete Function
	PhysXTestActor(const PhysXTestActor& _Other) = delete;
	PhysXTestActor(PhysXTestActor&& _Other) noexcept = delete;
	PhysXTestActor& operator=(const PhysXTestActor& _Other) = delete;
	PhysXTestActor& operator=(PhysXTestActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class PhysXBoxGeometryComponent> pGeometryComp = nullptr;
	std::shared_ptr<class PhysXDynamicActorComponent> pDynamicActorComp = nullptr;
	std::shared_ptr<class PhysXTriangleComponent> pTriangleComp = nullptr;
	std::shared_ptr<class PhysXConvexComponent> pConvexComp = nullptr;
};

