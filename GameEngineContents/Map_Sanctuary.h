#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class Map_Sanctuary : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_Sanctuary();
	~Map_Sanctuary();

	// delete Function
	Map_Sanctuary(const Map_Sanctuary& _Other) = delete;
	Map_Sanctuary(Map_Sanctuary&& _Other) noexcept = delete;
	Map_Sanctuary& operator=(const Map_Sanctuary& _Other) = delete;
	Map_Sanctuary& operator=(Map_Sanctuary&& _Other) noexcept = delete;

	inline std::shared_ptr<class ContentFBXRenderer> GetNaviMeshRenderer() const
	{
		return m_pNaviRenderer;
	}

	inline std::shared_ptr<class FrogFloor> GetFloor() const
	{
		return m_pFrogFloor;
	}

	void NaviRenderSwitch();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();
	void Create_PhysXComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;

	std::shared_ptr<class FrogFloor> m_pFrogFloor = nullptr;

	const float4 m_MapRot = float4{ 0 , -135 , 0 };
	const float4 m_NavRot = float4{ 0, 45, 0 };
	const float4 m_MapPos = float4{ 0, 0 , 0 };
};
