#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 보스 타일맵 경기장
class FrogFloor : public GameEngineActor
{
public:
	friend class Map_Sanctuary;

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

	inline std::vector<std::vector<std::shared_ptr<class SecretTile>>> GetTiles() const
	{
		return m_vTiles;
	}

	inline std::vector<std::shared_ptr<class RuinsWall>> GetWalls() const
	{
		return m_vWalls;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void OnRotation()
	{
		m_bRotation = true;
	}

	void OffRotation()
	{
		m_bRotation = false;
	}

	const bool IsRotation() const
	{
		return m_bRotation;
	}

	void DestroyTile(const int _Y, const int _X);
	bool IsTile(const int _Y, const int _X);
	void ResetTile();
	void ShakeTile(const int _Y, const int _X);

	void RotationUpdate(float _DeltaTime);
	
	void InitComponent();
	void Create_FireObject();
	void Create_TileObject();
	void Create_WallObject();

	std::shared_ptr<class ContentFBXRenderer> m_pHingeRenderer = nullptr;

	std::vector <std::shared_ptr<class FireObject>> m_vFireObjects = std::vector<std::shared_ptr<class FireObject>>();
	float4 m_FireObjScale = float4{ 50, 50 , 50 };

	// tile
	std::vector<std::vector<std::shared_ptr<class SecretTile>>> m_vTiles = std::vector<std::vector<std::shared_ptr<class SecretTile>>>();
	const float4 m_TileInitPos = float4{ -390, 55, 725 };
	int m_iTileSize = 25;
	float m_fTileMovePos = 396.0f;

	// wall 
	std::vector<std::shared_ptr<class RuinsWall>> m_vWalls = std::vector<std::shared_ptr<class RuinsWall>>();

	size_t m_Width = 5;
	size_t m_Height = 5;

	float4 m_f4FloorPos = float4{ -3871, -197, 3950 };

	bool m_bRotation = false;
};
