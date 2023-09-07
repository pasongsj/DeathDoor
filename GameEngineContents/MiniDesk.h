#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class MiniDesk : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniDesk();
	~MiniDesk();

	// delete Function
	MiniDesk(const MiniDesk& _Other) = delete;
	MiniDesk(MiniDesk&& _Other) noexcept = delete;
	MiniDesk& operator=(const MiniDesk& _Other) = delete;
	MiniDesk& operator=(MiniDesk&& _Other) noexcept = delete;

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
