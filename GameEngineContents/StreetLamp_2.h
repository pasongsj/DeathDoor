#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class StreetLamp_2 : public GameEngineActor
{
public:
	// constrcuter destructer
	StreetLamp_2();
	~StreetLamp_2();

	// delete Function
	StreetLamp_2(const StreetLamp_2& _Other) = delete;
	StreetLamp_2(StreetLamp_2&& _Other) noexcept = delete;
	StreetLamp_2& operator=(const StreetLamp_2& _Other) = delete;
	StreetLamp_2& operator=(StreetLamp_2&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pComp;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pComp = nullptr;
};
