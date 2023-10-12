#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class CullingTrigger : public GameEngineActor
{
public:
	// constrcuter destructer
	CullingTrigger();
	~CullingTrigger();

	// delete Function
	CullingTrigger(const CullingTrigger& _Other) = delete;
	CullingTrigger(CullingTrigger&& _Other) noexcept = delete;
	CullingTrigger& operator=(const CullingTrigger& _Other) = delete;
	CullingTrigger& operator=(CullingTrigger&& _Other) noexcept = delete;

	inline void TriggerOn()
	{
		m_bIsActivate = true;
	}

	inline void TriggerOff()
	{
		m_bIsActivate = false;
	}

	void Set_CullingObject(std::shared_ptr<class CullingObject> _Obj, std::shared_ptr<class CullingObject> _Obj2);
	
	void On_CullingObject();
	void Off_CullingObject();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	bool m_bIsActivate = false;

	// 대충 트리거로 사용할 메쉬 아무거나 
	// 피직스 박스 컴포넌트 
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;


	// 세팅을 해준다. 
	std::weak_ptr<class CullingObject> m_pCullingObject_1;
	std::weak_ptr<class CullingObject> m_pCullingObject_2;

};
