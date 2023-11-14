#pragma once
#include "ContentLevel.h"

// 설명 :
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

	void StageClearCheck();

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
	void Create_BossFrog();
	void Create_WaterBox();
	void Create_TriggerObject();
	void Create_TileManager();

	void ObjectFadeEffectUpdate(float _DeltaTime);

	const float4 m_CameraPos = float4{ -5200, 500, 5180 };/*float4{ -450, 1700, -1500 };*/
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

	// 엔딩 관련 
	std::weak_ptr<class ShortCutDoor> m_pDoor;
	std::weak_ptr<class Ladder> m_pLadder;
	std::weak_ptr<class SecretTile> m_pTile;
	std::weak_ptr<class SecretTile> m_pTile2;
	std::weak_ptr<class SecretTile> m_pTile3;


	bool m_bIsClear = false;
	bool m_bExitDoor = false;
	
	float m_FadeUpdateTime = 1.5f;

	GameEngineSoundPlayer BGM = nullptr;
	
};
