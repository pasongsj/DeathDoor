#pragma once
#include "PhysXLevel.h"

// Ό³Έν :
class OfficeLevel : public PhysXLevel
{
public:
	// constrcuter destructer
	OfficeLevel();
	~OfficeLevel();

	// delete Function
	OfficeLevel(const OfficeLevel& _Other) = delete;
	OfficeLevel(OfficeLevel&& _Other) noexcept = delete;
	OfficeLevel& operator=(const OfficeLevel& _Other) = delete;
	OfficeLevel& operator=(OfficeLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};
