#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FrogFloor : public GameEngineActor
{
public:
	// constrcuter destructer
	FrogFloor();
	~FrogFloor();

	// delete Function
	FrogFloor(const FrogFloor& _Other) = delete;
	FrogFloor(FrogFloor&& _Other) noexcept = delete;
	FrogFloor& operator=(const FrogFloor& _Other) = delete;
	FrogFloor& operator=(FrogFloor&& _Other) noexcept = delete;

	inline std::shared_ptr<class ContentFBXRenderer> GetHingeRender() const
	{
		return m_pHingeRenderer;
	}

	inline std::vector<std::shared_ptr<class SecretTile>> GetTiles() const
	{
		return m_vTiles;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();
	void Create_FireObject();
	void Create_TileObject();

	std::shared_ptr<class ContentFBXRenderer> m_pHingeRenderer = nullptr;

	float4 m_FireObjScale = float4{ 50, 50 , 50 };

	std::vector<std::shared_ptr<class SecretTile>> m_vTiles = std::vector<std::shared_ptr<class SecretTile>>();
	const float4 m_TileInitPos = float4{ -390, 25, 725 };

	float m_fTileMovePos = 396.0f;

	size_t m_Width = 5;
	size_t m_Height = 5;

};
