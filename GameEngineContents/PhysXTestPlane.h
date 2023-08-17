#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PhysXTestPlane :public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTestPlane();
	~PhysXTestPlane();

	// delete Function
	PhysXTestPlane(const PhysXTestPlane& _Other) = delete;
	PhysXTestPlane(PhysXTestPlane&& _Other) noexcept = delete;
	PhysXTestPlane& operator=(const PhysXTestPlane& _Other) = delete;
	PhysXTestPlane& operator=(PhysXTestPlane&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

