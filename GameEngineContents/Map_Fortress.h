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

	inline std::vector<std::shared_ptr<class CullingTrigger>>& GetCullingTrigger()
	{
		return m_vCullingTriggers;
	}

	inline std::vector<std::shared_ptr<class CullingObject>>& GetCullingObject()
	{
		return m_vCullingObjects;
	}

	void NaviRenderSwitch();
	void TriggerSwitch();

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

	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;

	size_t m_iTriggerSize = 20;
	size_t m_iCullingObject_Size = 17;
	std::vector<std::shared_ptr<class CullingTrigger>> m_vCullingTriggers = std::vector<std::shared_ptr<class CullingTrigger>>();
	std::vector<std::shared_ptr<class CullingObject>> m_vCullingObjects = std::vector<std::shared_ptr<class CullingObject>>();

	bool m_bTriggerSwitch = true;	

	// Cube
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube2 = nullptr;

	// Start에서 5도 더해줘서 135도임 
	const float4 m_MapRot = float4{ 0 , -130 , 0 };
	const float4 m_MapPos = float4{ 0, 0, 0 };
};
