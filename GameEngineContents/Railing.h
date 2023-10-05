#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Railing : public GameEngineActor
{
public:
	// constrcuter destructer
	Railing();
	~Railing();

	// delete Function
	Railing(const Railing& _Other) = delete;
	Railing(Railing&& _Other) noexcept = delete;
	Railing& operator=(const Railing& _Other) = delete;
	Railing& operator=(Railing&& _Other) noexcept = delete;

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
	std::shared_ptr<class PhysXBoxComponent > m_pComp = nullptr;
};
