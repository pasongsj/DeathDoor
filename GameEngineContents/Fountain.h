#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Fountain : public GameEngineActor
{
public:
	// constrcuter destructer
	Fountain();
	~Fountain();

	// delete Function
	Fountain(const Fountain& _Other) = delete;
	Fountain(Fountain&& _Other) noexcept = delete;
	Fountain& operator=(const Fountain& _Other) = delete;
	Fountain& operator=(Fountain&& _Other) noexcept = delete;

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
