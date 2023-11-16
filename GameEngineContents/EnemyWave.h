#pragma once
#include "FSMObjectBase.h"

class EnemyBase;
struct EnemySturct
{
	bool m_bIsDeath = false;
	std::shared_ptr<EnemyBase> m_pEnemy = nullptr;
};

// 설명 :
class EnemyWave : public FSMObjectBase
{
public:
	// constrcuter destructer
	EnemyWave();
	~EnemyWave();

	// delete Function
	EnemyWave(const EnemyWave& _Other) = delete;
	EnemyWave(EnemyWave&& _Other) noexcept = delete;
	EnemyWave& operator=(const EnemyWave& _Other) = delete;
	EnemyWave& operator=(EnemyWave&& _Other) noexcept = delete;

	void WaveStart();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent();

private:
	enum class WaveState
	{
		Stand_By,
		First_Wave,
		Second_Wave,
		Third_Wave,
		End,
		MAX,
	};

	// 몬스터를 소환할 위치
	// 어떤몬스터를 소환할지 정도만 정해줄수 있게 하면 좋을거 같은데. 

	float4 m_f4EnemyPos = float4{ -11800, 300, 12910 };
	float4 m_f4EnemyPos2 = float4{ -12300, 300, 13452 };
	float4 m_f4EnemyPos3 = float4{ -12379, 300, 12266 };

	std::vector<EnemySturct> m_vEnemys = std::vector<EnemySturct>();

	void SetFSMFUNC();
};
