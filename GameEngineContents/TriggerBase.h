#pragma once
#include "FSMObjectBase.h"



// Ό³Έν :
class TriggerBase : public FSMObjectBase
{
public:
	// constrcuter destructer
	TriggerBase();
	~TriggerBase();

	// delete Function
	TriggerBase(const TriggerBase& _Other) = delete;
	TriggerBase(TriggerBase&& _Other) noexcept = delete;
	TriggerBase& operator=(const TriggerBase& _Other) = delete;
	TriggerBase& operator=(TriggerBase&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

	void SetTriggerFunction(std::function<void()> _Func)
	{
		m_TriggerFunc = _Func;
	}

	bool IsPlayerInRange()
	{
		return CheckCollision(PhysXFilterGroup::PlayerDynamic);
	}

	bool IsHit()
	{
		return CheckCollision(PhysXFilterGroup::PlayerSkill);
	}
	bool IsKeyDown()
	{
		return GameEngineInput::IsDown("F");
	}

protected:

	virtual void InitComponent() {};

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXTriggerComponent = nullptr;
	bool m_bIsOpen = false;
	std::function<void()> m_TriggerFunc;

private:

	enum class LeverState
	{
		CLOSE,
		OPEN,
		OPEND,
	};



};

