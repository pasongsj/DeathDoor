#pragma once
#include "TriggerBase.h"

// Ό³Έν :
class Frog_Septre : public TriggerBase
{
public:
	// constrcuter destructer
	Frog_Septre();
	~Frog_Septre();

	// delete Function
	Frog_Septre(const Frog_Septre& _Other) = delete;
	Frog_Septre(Frog_Septre&& _Other) noexcept = delete;
	Frog_Septre& operator=(const Frog_Septre& _Other) = delete;
	Frog_Septre& operator=(Frog_Septre&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();

};

