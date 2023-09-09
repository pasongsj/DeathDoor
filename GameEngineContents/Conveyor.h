#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Conveyor : public GameEngineActor
{
public:
	// constrcuter destructer
	Conveyor();
	~Conveyor();

	// delete Function
	Conveyor(const Conveyor& _Other) = delete;
	Conveyor(Conveyor&& _Other) noexcept = delete;
	Conveyor& operator=(const Conveyor& _Other) = delete;
	Conveyor& operator=(Conveyor&& _Other) noexcept = delete;

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
