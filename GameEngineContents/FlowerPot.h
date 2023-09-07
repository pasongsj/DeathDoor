#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FlowerPot : public GameEngineActor
{
public:
	// constrcuter destructer
	FlowerPot();
	~FlowerPot();

	// delete Function
	FlowerPot(const FlowerPot& _Other) = delete;
	FlowerPot(FlowerPot&& _Other) noexcept = delete;
	FlowerPot& operator=(const FlowerPot& _Other) = delete;
	FlowerPot& operator=(FlowerPot&& _Other) noexcept = delete;

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
