#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PhysXTrigger :public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTrigger();
	~PhysXTrigger();

	// delete Function
	PhysXTrigger(const PhysXTrigger& _Other) = delete;
	PhysXTrigger(PhysXTrigger&& _Other) noexcept = delete;
	PhysXTrigger& operator=(const PhysXTrigger& _Other) = delete;
	PhysXTrigger& operator=(PhysXTrigger&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class PhysXBoxComponent> m_pBoxCompo = nullptr;

};

