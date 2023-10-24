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
	FSMObjectBase::Update(_DetltaTime);
}
