#include "PrecompileHeader.h"
#include "TriggerBase.h"

TriggerBase::TriggerBase() 
{
}

TriggerBase::~TriggerBase() 
{
}

void TriggerBase::Start()
{
	SetTrigger(true);
	InitFSM(TriggerState::MAX);
}

void TriggerBase::Update(float _DetltaTime)
{
	if (m_TriggerFunc!=nullptr)
	{
		m_TriggerFunc();
		m_TriggerFunc = nullptr;
	}
	FSMObjectBase::Update(_DetltaTime);
}
