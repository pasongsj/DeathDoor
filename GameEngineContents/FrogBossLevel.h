#pragma once
#include "ContentLevel.h"


// Ό³Έν :
class FrogBossLevel : public ContentLevel
{
public:
	// constrcuter destructer
	FrogBossLevel();
	~FrogBossLevel();

	// delete Function
	FrogBossLevel(const FrogBossLevel& _Other) = delete;
	FrogBossLevel(FrogBossLevel&& _Other) noexcept = delete;
	FrogBossLevel& operator=(const FrogBossLevel& _Other) = delete;
	FrogBossLevel& operator=(FrogBossLevel&& _Other) noexcept = delete;

	inline std::shared_ptr<class Map_Sanctuary> GetMap() const
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
	const float4 m_CameraPos = float4{ -450, 1700, -1500 };

	// 37µµ 
	const float4 m_CameraRot = float4{ 45 , 0 , 0 };

	void Set_PlayerStartPos();
	const float4 m_StartPos = float4{ -3100 , -180 , 3100 } ;

	void Set_BossStartPos();
	const float4 m_TestPos = float4{ -3636, -180, 4719 };
	const float4 m_BossStartPos = float4{ -4100 , -180 , 4100 };
	std::shared_ptr<class BossFrogMain> m_pBossFrog = nullptr;

	std::shared_ptr<class Map_Sanctuary> m_pMap = nullptr;
};
