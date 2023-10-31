#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class FortressLevel : public ContentLevel
{
public:
	// constrcuter destructer
	FortressLevel();
	~FortressLevel();

	// delete Function
	FortressLevel(const FortressLevel& _Other) = delete;
	FortressLevel(FortressLevel&& _Other) noexcept = delete;
	FortressLevel& operator=(const FortressLevel& _Other) = delete;
	FortressLevel& operator=(FortressLevel&& _Other) noexcept = delete;

	inline std::shared_ptr<class Map_Fortress> GetMap() const
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
	const float4 m_CameraPos = float4{ 0, 1500 , -1250 };
	const float4 m_CameraRot = float4{ 55 , 0 , 0 };

	void Set_PlayerStartPos();
	const float4 m_StartPos = float4{ -11800, 46, 6959 };

	std::shared_ptr<class Map_Fortress> m_pMap = nullptr;

	void Create_Manager();
	
	void Create_FieldEnemy();
	void Create_FieldObject();

	std::shared_ptr<class CullingManager> m_pCullingManager = nullptr;
};
