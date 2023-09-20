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

	std::shared_ptr<class PhysXCapsuleComponent>  GetCapsule()
	{
		return m_pCapsuleComp;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	


private:
	std::shared_ptr<class GameEngineFBXRenderer> m_pRenderer = nullptr;

	std::shared_ptr<class PhysXCapsuleComponent> m_pCapsuleComp = nullptr;
	std::shared_ptr<class PhysXBoxGeometryComponent> m_pGeometryComp = nullptr;
	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;
	std::shared_ptr<class PhysXConvexComponent> m_pConvexComp = nullptr;
	std::shared_ptr<class PhysXSphereComponent> m_pSphereComp = nullptr;
	std::shared_ptr<class PhysXControllerComponent> m_pControllerComp = nullptr;

};

