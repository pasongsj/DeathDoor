#pragma once
#include "ContentLevel.h"

enum class TestMapType
{
	Office,
	OldCrowFloor,
	None,
};

// Ό³Έν :
class MapTestLevel : public ContentLevel
{
public:
	// constrcuter destructer
	MapTestLevel();
	~MapTestLevel();

	// delete Function
	MapTestLevel(const MapTestLevel& _Other) = delete;
	MapTestLevel(MapTestLevel&& _Other) noexcept = delete;
	MapTestLevel& operator=(const MapTestLevel& _Other) = delete;
	MapTestLevel& operator=(MapTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	void InitTestLevel();

	inline void SetTestLevelType(TestMapType _Type)
	{
		m_Type = _Type;
	}

	TestMapType m_Type = TestMapType::None;

	float4 m_f4CameraRot = float4{ 45.0f , 0 , 0 };
	float4 m_f4CameraPos = float4{ 2800 , 2500 , -6500 };

};
