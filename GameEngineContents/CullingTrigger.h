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

	inline std::vector<int> Get_CullingObjectNumbers() const
	{
		return m_vCullingObj_Numbers;
	}

	void Set_CullingObjectNumber(int _Number0 , int _Number1, int _Number2, int _Number3 = INT_MAX);
	
	inline bool IsActivate()
	{
		return m_bIsActivate;
	}

	inline std::shared_ptr<class ContentFBXRenderer> GetRenderer()
	{
		return m_pRenderer;
	}
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	bool m_bIsActivate = false;

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;

	// 트리거가 오브젝트를 가지는게 아닌. 트리거가 활성화 할 컬링오브젝트의 인덱스넘버를 배열로가진다. 
	std::vector<int> m_vCullingObj_Numbers = std::vector<int>();
};
