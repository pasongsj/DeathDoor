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


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();
	void Create_Ground();
	void Create_Partition();
	void Create_PhysXComponent();

	void Create_StaticObject();
	void Create_ActiveObject();

	void Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel);

	std::shared_ptr<class PhysXTriangleComponent> m_pTriangleComp = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;

	// 컬링오브젝트 테스트 코드
	// 얘가 가지고 있을 필요가 있나?
	// 없는거같아 아니.. 가지고있어야되는거같은데 ㅋㅋㅋㅋ 
	std::shared_ptr<class CullingTrigger> m_pCullingTrigger = nullptr;
	std::shared_ptr<class CullingObject> m_pCullingObj1 = nullptr;
	std::shared_ptr<class CullingObject> m_pCullingObj2 = nullptr;
	std::shared_ptr<class CullingObject> m_pCullingObj3 = nullptr;
	

	std::vector<std::shared_ptr<class CullingTrigger>> m_vCullingTriggers = std::vector<std::shared_ptr<class CullingTrigger>>();
	std::vector<std::shared_ptr<class CullingObject>> m_vCullingObjects = std::vector<std::shared_ptr<class CullingObject>>();

	// 정해놔. 트리거는 몇개, 컬링오브젝트는 몇개로 할지
	
	// Section 
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section1 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section2 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Section3 = nullptr;

	// Cube
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Cube2 = nullptr;
	
	// 분할 obj 파트 
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part1 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part2 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part3 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part4 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part5 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part6 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part7 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part8 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part9 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part10 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part11 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part12 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part13 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part14 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part15 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer_Part16 = nullptr;
	



	const float4 m_MapRot = float4{ 0 , -130 , 0 };
	const float4 m_MapPos = float4{ 0, 0 , 0 };
};
