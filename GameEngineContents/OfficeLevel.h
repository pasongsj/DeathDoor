#pragma once
#include "ContentLevel.h"

enum class PrevLevelType
{
	OldCrowLevel,
	FortressLevel,
	BossFrogLevel,
	None,
};


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
	
	void SetPrevLevelType(PrevLevelType _Type)
	{
		m_eType = _Type;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitKey();
	void KeyUpdate(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;


private:
	const float4 m_CameraPos = float4{ 2800 , 2500 , -6500 };
	const float4 m_CameraRot = float4{ 45.0f , 0 , 0 };

	void Set_PlayerStartPos();

	float4 m_StartPos = float4 { 2610 , -740 , -5347 };

	// 숏컷도어 위치 
	// const float4 m_StartPos = float4{ 706, 1256, 4615 };
	const float4 m_TestStartPos = float4{ 1869, 570, 4110 };

	const float4 m_f4FortressToOfficePos = float4{ 1201, 1256, 5077 };
	const float4 m_f4OldCrowToOfficePos = float4{ -1156, 1652, 6140 };

	std::shared_ptr<class Map_Office> m_pMap = nullptr;

	void SetPointLight();
	void Create_TriggerObject();

	PrevLevelType m_eType = PrevLevelType::None;
};
