#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 스태틱 액터 기본 베이스로 

// 설명 :
class StreetLamp : public GameEngineActor
{
public:
	// constrcuter destructer
	StreetLamp();
	~StreetLamp();

	// delete Function
	StreetLamp(const StreetLamp& _Other) = delete;
	StreetLamp(StreetLamp&& _Other) noexcept = delete;
	StreetLamp& operator=(const StreetLamp& _Other) = delete;
	StreetLamp& operator=(StreetLamp&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pComp;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();
	
	std::shared_ptr<class GameEngineFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pComp = nullptr;
};
