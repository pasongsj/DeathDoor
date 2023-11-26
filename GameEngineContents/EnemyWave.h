#pragma once
#include "FSMObjectBase.h"

class EnemyBase;
struct EnemySturct
{
	bool m_bIsDeath = false;
	std::shared_ptr<EnemyBase> m_pEnemy = nullptr;
};

// ���� :
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

	// ���͸� ��ȯ�� ��ġ
	// ����͸� ��ȯ���� ������ �����ټ� �ְ� �ϸ� ������ ������. 

	float4 m_f4EnemyPos = float4{ -11800, 350, 12910 };
	float4 m_f4EnemyPos2 = float4{ -12300, 350, 13452 };
	float4 m_f4EnemyPos3 = float4{ -12379, 350, 12266 };

	std::vector<EnemySturct> m_vEnemys_1 = std::vector<EnemySturct>();
	std::vector<EnemySturct> m_vEnemys_2 = std::vector<EnemySturct>();
	std::vector<EnemySturct> m_vEnemys_3 = std::vector<EnemySturct>();

	std::vector<float4> m_vEnemysPos = { float4{ -11800, 350, 12910 } ,  float4{ -12300, 350, 13452 },float4{ -12379, 350, 12266 } };

	void SetFSMFUNC();
};