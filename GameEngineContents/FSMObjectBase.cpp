#include "PreCompileHeader.h"
#include "FSMObjectBase.h"

FSMObjectBase::FSMObjectBase() 
{
}

FSMObjectBase::~FSMObjectBase() 
{
}

void FSMObjectBase::Update(float _DeltaTime)
{
	if (true == FSMFunc.empty())
	{
		return;
	}

	if (CurState != NextState || true == ChangeStateForce)  // state가 변경되는 경우
	{
		if (FSMFunc.end() == FSMFunc.find(NextState))
		{
			MsgAssert("State에 해당하는 func이 생성되지 않았습니다");
		}

		if (nullptr != FSMFunc[CurState].End) // 전 FSM의 End Function
		{
			FSMFunc[CurState].End();
		}

		if (nullptr != ChangeFSMCallBack) // FSM이 변경될 때 일괄적으로 실행하는 것
		{
			ChangeFSMCallBack();
		}

		if (nullptr != FSMFunc[NextState].Start) // 바뀔 FSM의 Start Function
		{
			StateDuration = 0.0f;
			StateChecker = false;

			FSMFunc[NextState].Start();
		}
		CurState = NextState;
		ChangeStateForce = false;
	}
	if (nullptr != FSMFunc[CurState].Update) // FSM Update
	{
		StateDuration += _DeltaTime;
		FSMFunc[CurState].Update(_DeltaTime);
	}
	isPhysXCollision = 0;
}


