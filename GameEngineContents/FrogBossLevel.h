#pragma once
#include "PhysXLevel.h"


// ���� :
class FrogBossLevel : public PhysXLevel
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
	// 2800, 230, -6300
	const float4 m_CameraPos = float4{ 0, 0 , 0 };
	const float4 m_CameraRot = float4{ 0 , 0 , 0 };

	void Set_StartPos(std::shared_ptr<class Player> _Player);
	const float4 m_StartPos = float4::ZERONULL;
	// const float4 m_TestStartPos = float4{ 1869, 570, 4110 };


	std::shared_ptr<class Map_Sanctuary> m_pMap = nullptr;
};