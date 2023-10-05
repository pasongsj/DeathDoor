#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 :
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
	void Create_PhysXComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pNaviRenderer = nullptr;

	// 통맵 테스트 
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
};
