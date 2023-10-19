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
	const float4 m_StartPos = float4{ 0, 300, 0 } ;

	std::shared_ptr<class Map_Sanctuary> m_pMap = nullptr;
};
