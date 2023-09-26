#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SemiCircleTable : public GameEngineActor
{
public:
	// constrcuter destructer
	SemiCircleTable();
	~SemiCircleTable();

	// delete Function
	SemiCircleTable(const SemiCircleTable& _Other) = delete;
	SemiCircleTable(SemiCircleTable&& _Other) noexcept = delete;
	SemiCircleTable& operator=(const SemiCircleTable& _Other) = delete;
	SemiCircleTable& operator=(SemiCircleTable&& _Other) noexcept = delete;

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
