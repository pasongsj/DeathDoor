#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class LeverState
{
	CLOSE,
	OPEN,
	OPEND,
};


// Ό³Έν :
class Frog_Lever : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog_Lever();
	~Frog_Lever();

	// delete Function
	Frog_Lever(const Frog_Lever& _Other) = delete;
	Frog_Lever(Frog_Lever&& _Other) noexcept = delete;
	Frog_Lever& operator=(const Frog_Lever& _Other) = delete;
	Frog_Lever& operator=(Frog_Lever&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

	inline std::shared_ptr<class PhysXBoxComponent> GetTriggerComponent() const
	{
		return m_pPhysXTriggerComponent;
	}

	inline void SetState(LeverState _State)
	{
		m_eState = _State;
	}

	void SetTriggerFunction(std::function<void()> _Func)
	{
		m_TriggerFunc = _Func;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXTriggerComponent = nullptr;

	bool m_bIsOpen = false;

	std::function<void()> m_TriggerFunc;

	LeverState m_eState = LeverState::CLOSE;
};
