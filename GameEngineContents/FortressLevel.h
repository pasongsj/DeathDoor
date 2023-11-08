#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class FortressLevel : public ContentLevel
{
public:
	// constrcuter destructer
	FortressLevel();
	~FortressLevel();

	// delete Function
	FortressLevel(const FortressLevel& _Other) = delete;
	FortressLevel(FortressLevel&& _Other) noexcept = delete;
	FortressLevel& operator=(const FortressLevel& _Other) = delete;
	FortressLevel& operator=(FortressLevel&& _Other) noexcept = delete;

	inline std::shared_ptr<class Map_Fortress> GetMap() const
	{
		return m_pMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitKey();
	void KeyUpdate(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;


private:
	void Create_Light();
	void Create_Map();
	void Create_Player();
	void Create_WaterBox();

	const float4 m_CameraPos = float4{ 0, 1500 , -1250 };
	const float4 m_CameraRot = float4{ 55 , 0 , 0 };

	void Set_PlayerStartPos();
	const float4 m_StartPos = float4{ 0, 0, 0 };

	// const float4 m_WavePos = float4 { -12000, 306, 10800 };

	std::shared_ptr<class Map_Fortress> m_pMap = nullptr;

	void Create_Manager();
	
	void Create_FieldEnemy();
	void Create_FieldObject();

	std::shared_ptr<class CullingManager> m_pCullingManager = nullptr;
};
