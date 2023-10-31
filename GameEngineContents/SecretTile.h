#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TileState
{
	NORMAL,
	DESTROY,
};

struct TileIndex
{
	int X = -1;
	int Y = -1;
};

// ���� :
class SecretTile : public GameEngineActor
{
public:
	// constrcuter destructer
	SecretTile();
	~SecretTile();

	// delete Function
	SecretTile(const SecretTile& _Other) = delete;
	SecretTile(SecretTile&& _Other) noexcept = delete;
	SecretTile& operator=(const SecretTile& _Other) = delete;
	SecretTile& operator=(SecretTile&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

	inline std::shared_ptr<class ContentFBXRenderer> GetRender() const
	{
		return m_pRenderer;
	}

	inline void SetState(TileState _State)
	{
		m_eState = _State;
	}

	inline void SetTileIndex(const int _X, const int _Y)
	{
		m_TileIndex.X = _X;
		m_TileIndex.Y = _Y;
	}

	inline float GetTileSize() const
	{
		return m_TileSize;
	}

	// ���⼭ ���� Ȱ��ȭ ���°� �ƴ϶�� 
	// �������� ������������Ʈ�� off ��ų�ǵ�
	// �ϴ� �ǰ� �����. ���̴��� ���߿� ����.
	
	void InActive();
	void Active();

	bool IsActive()
	{
		if (true == m_bIsActive)
		{
			return true;
		}

		return false;
	}

	void TileShake(float _DeltaTime);

	void OnShake(const float _ShakeTime)
	{
		m_bIsActive = false;
		m_bShake = true;
		m_fShakeTime = _ShakeTime;
	}

	void OffShake();

	void SetActiveType(bool Type)
	{
		m_bIsActive = Type;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;

	TileState m_eState = TileState::NORMAL;

	TileIndex m_TileIndex = {};

	// Ÿ�ϻ����� 
	float m_TileSize = 0.0f;

	bool m_bIsActive = true;
	
	bool m_bShake = false;
	float m_fShakeTime = 2.0f;
};
