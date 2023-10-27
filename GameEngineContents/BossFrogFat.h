#pragma once
#include "BossFrog.h"

// Ό³Έν :
class BossFrogFat : public BossFrog
{
public:
	// constrcuter destructer
	BossFrogFat();
	~BossFrogFat();

	// delete Function
	BossFrogFat(const BossFrogFat& _Other) = delete;
	BossFrogFat(BossFrogFat&& _Other) noexcept = delete;
	BossFrogFat& operator=(const BossFrogFat& _Other) = delete;
	BossFrogFat& operator=(BossFrogFat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void InitAnimation() override;
	void SetFSMFUNC() override;

private:

	const float4 WeaponPivotPos = float4{ 0.0f,0.1f,0.0f };
	const float4 WeaponPivotRot = float4{ -85.03f,40.0f,0.0f };
	std::shared_ptr<class ContentFBXRenderer> WeaponRenderer = nullptr;


	enum class BossFrogFatState
	{
		IDLE,
		MAX,
	};
};

