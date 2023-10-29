#pragma once
#include "ContentLevel.h"

// M : NaviRender OnOff 스위치 

// 설명 :
class OfficeLevel : public ContentLevel
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
	const float4 m_CameraPos = float4{ 2800 , 2500 , -6500 };
	const float4 m_CameraRot = float4{ 45.0f , 0 , 0 };

	void Set_PlayerStartPos();
	const float4 m_StartPos = float4 { 2610 , -740 , -5347 };
	const float4 m_TestStartPos = float4{ 1869, 570, 4110 };

	std::shared_ptr<class Map_Office> m_pMap = nullptr;

	void SetPointLight();
};
