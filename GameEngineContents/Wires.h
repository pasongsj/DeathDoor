#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wires : public GameEngineActor
{
public:
	// constrcuter destructer
	Wires();
	~Wires();

	// delete Function
	Wires(const Wires& _Other) = delete;
	Wires(Wires&& _Other) noexcept = delete;
	Wires& operator=(const Wires& _Other) = delete;
	Wires& operator=(Wires&& _Other) noexcept = delete;

	inline std::shared_ptr<class ContentFBXRenderer> GetRenderer() const
	{
		return m_pRenderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
};
