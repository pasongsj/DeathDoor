#pragma once
#include "PhysXLevel.h"


// M : NaviRender OnOff 스위치 

// 설명 :
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

	void InitKey();
	void KeyUpdate(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;


private:
	// 2800, 230, -6300
	const float4 m_CameraPos = float4{ 2800 , 300 , -6500 };
	const float4 m_CameraRot = float4{ 35 , 0 , 0 };

	void Set_StartPos(std::shared_ptr<class Player> _Player);
	const float4 m_StartPos = float4 { 2610 , -740 , -5347 };
	const float4 m_TestStartPos = float4{ 0, 50, 0 };
	

	std::shared_ptr<class Map_Office> m_pMap = nullptr;
};
