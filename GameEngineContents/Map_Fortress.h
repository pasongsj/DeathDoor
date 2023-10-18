#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Map_Fortress : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_Fortress();
	~Map_Fortress();

	// delete Function
	Map_Fortress(const Map_Fortress& _Other) = delete;
	Map_Fortress(Map_Fortress&& _Other) noexcept = delete;
	Map_Fortress& operator=(const Map_Fortress& _Other) = delete;
	Map_Fortress& operator=(Map_Fortress&& _Other) noexcept = delete;

	std::shared_ptr<class ContentFBXRenderer> GetNaviMeshRenderer() const
	{
		return m_pNaviRenderer;
	}

	void NaviRenderSwitch();

	inline std::vector<std::shared_ptr<class CullingTrigger>>& GetCullingTrigger()
	{
		return m_vCullingTriggers;
	}

	inline std::vector<std::shared_ptr<class CullingObject>>& GetCullingObject()
	{
		return m_vCullingObjects;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();
	void Create_Ground();
	void Create_CullingObject();
	void Set_CullingTrigger();
	void Set_CullingTrigger_WorldPos();
	void Set_CullingObject();
	void Create_PhysXComponent();

	void Create_StaticObject();
	void Create_ActiveObject();

	void Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel);

	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;

	// 나중에 설정함 
	size_t m_iTriggerSize = 2;
	// 나중에 설정함  
	size_t m_iCullingObject_Size = 4;
	std::vector<std::shared_ptr<class CullingTrigger>> m_vCullingTriggers = std::vector<std::shared_ptr<class CullingTrigger>>();
	std::vector<std::shared_ptr<class CullingObject>> m_vCullingObjects = std::vector<std::shared_ptr<class CullingObject>>();

	// Section 
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section1 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section2 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section3 = nullptr;

	// Cube
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube2 = nullptr;


	const float4 m_MapRot = float4{ 0 , -130 , 0 };
	const float4 m_MapPos = float4{ 0, 0 , 0 };
};
