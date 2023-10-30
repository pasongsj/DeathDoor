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

// 설명 :
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

	// 여기서 내가 활성화 상태가 아니라면 
	// 렌더러와 피직스컴포넌트를 off 시킬건데
	// 일단 되게 만들고. 쉐이더는 나중에 생각.
	
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;

	TileState m_eState = TileState::NORMAL;

	TileIndex m_TileIndex = {};

	// 타일사이즈 
	float m_TileSize = 0.0f;

	bool m_bIsActive = true;
};
