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


	bool TriggerHitCheck()
	{
		if (true== IsPlayerInRange()&&true == IsHit())
		{
			return true;
		}
		return false;
	}

	bool TriggerKeyCheck()
	{
		if (true == IsPlayerInRange() && true == IsKeyDown())
		{
			return true;
		}
		return false;
	}

protected:
	void Start() override;
	void Update(float _DetltaTime) override;

	enum class TriggerState
	{
		OFF,
		PROGRESS,
		ON,
		MAX
	};

	virtual void InitComponent() {};

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
	bool m_bTrigger = false;
	std::function<void()> m_TriggerFunc;

private:

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


};

