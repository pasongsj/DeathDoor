#pragma once
#include "TriggerBase.h"


// Ό³Έν :
class ShortCutDoor : public TriggerBase
{
public:
	// constrcuter destructer
	ShortCutDoor();
	~ShortCutDoor();

	// delete Function
	ShortCutDoor(const ShortCutDoor& _Other) = delete;
	ShortCutDoor(ShortCutDoor&& _Other) noexcept = delete;
	ShortCutDoor& operator=(const ShortCutDoor& _Other) = delete;
	ShortCutDoor& operator=(ShortCutDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();
};