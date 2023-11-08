#pragma once
#include "ContentLevel.h"


// Ό³Έν :
class BossFrogLevel : public ContentLevel
{
public:
	// constrcuter destructer
	BossFrogLevel();
	~BossFrogLevel();

	// delete Function
	BossFrogLevel(const BossFrogLevel& _Other) = delete;
	BossFrogLevel(BossFrogLevel&& _Other) noexcept = delete;
	BossFrogLevel& operator=(const BossFrogLevel& _Other) = delete;
	BossFrogLevel& operator=(BossFrogLevel&& _Other) noexcept = delete;

	inline std::weak_ptr<class Map_Sanctuary> GetMap() const
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
	const float4 m_CameraPos = float4{ -5200, 500, 5180 };/*float4{ -450, 1700, -1500 };*/

	// 37µµ 
	const float4 m_CameraRot = float4{ 55 , 0 , 0 };

	void Set_PlayerStartPos();
	const float4 m_StartPos = float4{ -3100 , -180 , 3100 } ;

	void Set_BossStartPos();
	const float4 m_TestPos = float4{ -5200, 500, 5180 };
	const float4 m_BossStartPos = float4{ -4100 , -180 , 4100 };
	bool isFatPhase = false;
	float SecondPhaseStartTime = 0.0f;

	std::shared_ptr<class BossFrog> m_pBossFrog = nullptr;
	std::weak_ptr<class Map_Sanctuary> m_pMap;

};
