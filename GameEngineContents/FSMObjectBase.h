#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>
#include <map>

// 설명 :
class FSMObjectBase : public GameEngineActor
{
public:
	// constrcuter destructer
	FSMObjectBase();
	~FSMObjectBase();

	// delete Function
	FSMObjectBase(const FSMObjectBase& _Other) = delete;
	FSMObjectBase(FSMObjectBase&& _Other) noexcept = delete;
	FSMObjectBase& operator=(const FSMObjectBase& _Other) = delete;
	FSMObjectBase& operator=(FSMObjectBase&& _Other) noexcept = delete;

protected:

	// state
	template<typename Enumclass>
	inline void SetNextState(Enumclass _Num,bool _Force = false) //다음 State 설정
	{
		NextState = static_cast<int>(_Num);
		ChangeStateForce = _Force;
	}

	template<typename Enumclass> // 현재 State Get
	inline Enumclass GetCurState()
	{
		return static_cast<Enumclass>(CurState);
	}

	template<typename Enumclass>
	inline void InitFSM(Enumclass _Num) // FSM Function 생성
	{
		for (int i = 0; i < static_cast<int>(_Num); ++i)
		{
			StateFunctionParameter NewStatePara;
			FSMFunc[i] = NewStatePara;
		}
	}

	// FSM Function 설정
	template<typename Enumclass>
	inline void SetFSM(Enumclass _Num, std::function<void()> _Start, std::function<void(float _Delta)> _Update, std::function<void()> _End)
	{
		SetFSM(static_cast<int>(_Num), _Start, _Update, _End);
	}

	inline void SetFSM(int _Num, std::function<void()> _Start, std::function<void(float _Delta)> _Update, std::function<void()> _End)
	{
		FSMFunc[_Num].Start = _Start;
		FSMFunc[_Num].Update = _Update;
		FSMFunc[_Num].End = _End;

	}

	inline void SetChangeFSMCallBack(std::function<void()> _Func) // FSM이 바뀔 때 마다 공통적으로 실행
	{
		ChangeFSMCallBack = _Func;
	}

	void Update(float _DeltaTime) override;

	inline float GetStateDuration()
	{
		return StateDuration;
	}
	inline void ResetStateDuration()
	{
		StateDuration = 0.0f;
	}

	inline bool GetStateChecker()
	{
		return StateChecker;
	}

	inline void SetStateCheckerOn()
	{
		StateChecker = true;
	}

	inline void SetStateCheckerOff()
	{
		StateChecker = false;
	}

	inline void SetStateChecker(bool _Check)
	{
		StateChecker = _Check;
	}

	inline void SetTrigger(bool _Value)
	{
		IsTrigger = _Value;
	}

private:
	class StateFunctionParameter
	{
	public:
		std::function<void()> Start = nullptr;
		std::function<void(float _Delta)> Update = nullptr;
		std::function<void()> End = nullptr;
	};

	std::map<int, StateFunctionParameter> FSMFunc;
	std::function<void()> ChangeFSMCallBack = nullptr;
	int CurState = 0;
	int NextState = 0;

	// Update
	float StateDuration = 0.0f; // 해당하는 State가 지속되는 시간
	bool StateChecker = false;	// Action확인용 bool값

	bool ChangeStateForce = false;	// SetNextState에서 현재 State를 (stateEnd)끝내고 (stateStart)시작하려 할 때 사용

	bool IsTrigger = false;

};

