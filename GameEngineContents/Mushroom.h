#pragma once
#include "TriggerBase.h"

// Ό³Έν :
class Mushroom : public TriggerBase
{
public:
	// constrcuter destructer
	Mushroom();
	~Mushroom();

	// delete Function
	Mushroom(const Mushroom& _Other) = delete;
	Mushroom(Mushroom&& _Other) noexcept = delete;
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();

};

