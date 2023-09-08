#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Bench : public GameEngineActor
{
public:
	// constrcuter destructer
	Bench();
	~Bench();

	// delete Function
	Bench(const Bench& _Other) = delete;
	Bench(Bench&& _Other) noexcept = delete;
	Bench& operator=(const Bench& _Other) = delete;
	Bench& operator=(Bench&& _Other) noexcept = delete;

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
	std::shared_ptr<class PhysXBoxComponent > m_pComp = nullptr;
};
