#pragma once
#include "TriggerBase.h"

// 설명 :
class Ladder : public TriggerBase
{
public:
	// constrcuter destructer
	Ladder();
	~Ladder();

	// delete Function
	Ladder(const Ladder& _Other) = delete;
	Ladder(Ladder&& _Other) noexcept = delete;
	Ladder& operator=(const Ladder& _Other) = delete;
	Ladder& operator=(Ladder&& _Other) noexcept = delete;


	void SetHidden(bool _Value)
	{
		m_bHidden = _Value; 
		if (true == m_bHidden)
		{
			SetNextState(TriggerState::OFF,true);
		}
	}

	void SetHeight(int _Amount)
	{
		//Ladder clone의 크기 확인해서 한개의 크기만큼 줄여버리기
		m_fHeight = static_cast<float>(_Amount);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();

	bool m_bHidden = false;

	float m_fHeight = 0.f;

	void SetLadderPosition();

	

};
