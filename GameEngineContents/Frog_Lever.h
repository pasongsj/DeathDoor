#pragma once
#include "TriggerBase.h"



// Ό³Έν :
class Frog_Lever :  public TriggerBase
{
public:
	// constrcuter destructer
	Frog_Lever();
	~Frog_Lever();

	// delete Function
	Frog_Lever(const Frog_Lever& _Other) = delete;
	Frog_Lever(Frog_Lever&& _Other) noexcept = delete;
	Frog_Lever& operator=(const Frog_Lever& _Other) = delete;
	Frog_Lever& operator=(Frog_Lever&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;

private:
	enum class LeverState
	{
		CLOSE,
		OPEN,
		OPEND,
		MAX
	};

};
