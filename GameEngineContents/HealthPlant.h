#pragma once
#include "TriggerBase.h"

// Ό³Έν :
class HealthPlant : public TriggerBase
{
public:
	// constrcuter destructer
	HealthPlant();
	~HealthPlant();

	// delete Function
	HealthPlant(const HealthPlant& _Other) = delete;
	HealthPlant(HealthPlant&& _Other) noexcept = delete;
	HealthPlant& operator=(const HealthPlant& _Other) = delete;
	HealthPlant& operator=(HealthPlant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();
	InteractionData m_sData;
};

