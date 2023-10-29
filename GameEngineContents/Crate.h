#pragma once
#include "TriggerBase.h"


// 설명 :
class Crate : public TriggerBase
{
public:
	// constrcuter destructer
	Crate();
	~Crate();

	// delete Function
	Crate(const Crate& _Other) = delete;
	Crate(Crate&& _Other) noexcept = delete;
	Crate& operator=(const Crate& _Other) = delete;
	Crate& operator=(Crate&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer1 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer2 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> m_pRenderer3 = nullptr;

	int m_iHP = 3;
	bool CheckBreak()
	{
		if (true == IsHit())// 플레이어로부터 공격을 받는다면 
		{
			--m_iHP;
			isPhysXCollision = 0;
		}
		if (m_iHP<=0)
		{
			return true;
		}
		return false;
	}
};
