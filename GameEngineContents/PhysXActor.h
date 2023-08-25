#pragma once

// Ό³Έν :
class PhysXActor
{
public:
	// constrcuter destructer
	PhysXActor();
	~PhysXActor();

	// delete Function
	PhysXActor(const PhysXActor& _Other) = delete;
	PhysXActor(PhysXActor&& _Other) noexcept = delete;
	PhysXActor& operator=(const PhysXActor& _Other) = delete;
	PhysXActor& operator=(PhysXActor&& _Other) noexcept = delete;

protected:

private:

};

