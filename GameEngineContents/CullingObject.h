#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class CullingObject : public GameEngineActor
{
public:
	// constrcuter destructer
	CullingObject();
	~CullingObject();

	// delete Function
	CullingObject(const CullingObject& _Other) = delete;
	CullingObject(CullingObject&& _Other) noexcept = delete;
	CullingObject& operator=(const CullingObject& _Other) = delete;
	CullingObject& operator=(CullingObject&& _Other) noexcept = delete;

	inline bool IsCulling() const
	{
		return m_bIsCulling;
	}

	void InitComponent(const std::string& _MeshName);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool m_bIsCulling = true;
	
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;



	// 트리거 액터를 하나두고, 배치한다. 
	// 플레이어가 그 트리거와 충돌했다면, 해당 트리거와 연결 되어 있는 모든 Renderer를 On ? 
};
