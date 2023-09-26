#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MiniPost : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniPost();
	~MiniPost();

	// delete Function
	MiniPost(const MiniPost& _Other) = delete;
	MiniPost(MiniPost&& _Other) noexcept = delete;
	MiniPost& operator=(const MiniPost& _Other) = delete;
	MiniPost& operator=(MiniPost&& _Other) noexcept = delete;

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
