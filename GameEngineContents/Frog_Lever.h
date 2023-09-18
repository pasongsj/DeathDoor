#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Frog_Lever : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog_Lever();
	~Frog_Lever();

	// delete Function
	Frog_Lever(const Frog_Lever& _Other) = delete;
	Frog_Lever(Frog_Lever&& _Other) noexcept = delete;
	Frog_Lever& operator=(const Frog_Lever& _Other) = delete;
	Frog_Lever& operator=(Frog_Lever&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<GameEngineFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;
};
