#pragma once
#include "FSMObjectBase.h"


enum class LeverType
{
	NONE,
	HIT,
	KEY,
};

// Ό³Έν :
class LeverBase : public FSMObjectBase
{
public:
	// constrcuter destructer
	LeverBase();
	~LeverBase();

	// delete Function
	LeverBase(const LeverBase& _Other) = delete;
	LeverBase(LeverBase&& _Other) noexcept = delete;
	LeverBase& operator=(const LeverBase& _Other) = delete;
	LeverBase& operator=(LeverBase&& _Other) noexcept = delete;

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

	bool IsHit();
	bool IsKeyDown();

protected:

	virtual void InitComponent() {};

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXTriggerComponent = nullptr;
	bool m_bIsOpen = false;
	std::function<void()> m_TriggerFunc;
	//LeverState m_eState = LeverState::CLOSE;

	LeverType m_eType = LeverType::NONE;

private:

	enum class LeverState
	{
		CLOSE,
		OPEN,
		OPEND,
	};



};

