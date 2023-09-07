#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MiniOffice : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniOffice();
	~MiniOffice();

	// delete Function
	MiniOffice(const MiniOffice& _Other) = delete;
	MiniOffice(MiniOffice&& _Other) noexcept = delete;
	MiniOffice& operator=(const MiniOffice& _Other) = delete;
	MiniOffice& operator=(MiniOffice&& _Other) noexcept = delete;

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
