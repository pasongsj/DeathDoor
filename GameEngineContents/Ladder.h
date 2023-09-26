#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Ladder : public GameEngineActor
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

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
};
