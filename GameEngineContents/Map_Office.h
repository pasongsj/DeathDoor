#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Map_Office : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_Office();
	~Map_Office();

	// delete Function
	Map_Office(const Map_Office& _Other) = delete;
	Map_Office(Map_Office&& _Other) noexcept = delete;
	Map_Office& operator=(const Map_Office& _Other) = delete;
	Map_Office& operator=(Map_Office&& _Other) noexcept = delete;


	std::shared_ptr<class ContentFBXRenderer> GetNaviMeshRenderer() const
	{
		return m_pNaviRenderer;
	}

	void NaviRenderSwitch();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	void Create_StaticObject();
	void Create_ActiveObject();

	void Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel);
	void Create_MainOfficeObject(std::shared_ptr<class GameEngineLevel> _CurLevel);
	void Create_RailingObject(std::shared_ptr<class GameEngineLevel> _CurLevel);


	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;

	const float4 m_MapRot = float4{ 0 , -135 , 0 };
	const float4 m_MapPos = float4{ -20, -8 , -30 };

	float4 m_f4BankerPos = float4{ 2115, 656, 5069 };
	std::shared_ptr<class ContentFBXRenderer> m_pBankerRender = nullptr;
	
	float4 m_f4HollCrow1Pos = float4{ 3100, 556, 4050 };

	std::shared_ptr<class ContentFBXRenderer> m_pHall_Crow_1 = nullptr;

	float4 m_f4HollCrow2Pos = float4{ 1277, 556, 4155 };
	std::shared_ptr<class ContentFBXRenderer> m_pHall_Crow_2 = nullptr;

	std::shared_ptr<class ContentFBXRenderer> m_pHall_Crow_3 = nullptr;
	float4 m_f4HollCrow3Pos = float4{ 2158, 565, 4175 };

};
