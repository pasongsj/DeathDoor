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
	const float4 m_CameraPos = float4{ 2800 , 230 , -6300 };
	const float4 m_CameraRot = float4{ 35 , 0 , 0 };

	void Set_StartPos(std::shared_ptr<class Player> _Player);
	const float4 m_StartPos = float4 { 2610 , -574 , -5347 };
};
