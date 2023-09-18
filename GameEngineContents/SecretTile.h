#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SecretTile : public GameEngineActor
{
public:
	// constrcuter destructer
	SecretTile();
	~SecretTile();

	// delete Function
	SecretTile(const SecretTile& _Other) = delete;
	SecretTile(SecretTile&& _Other) noexcept = delete;
	SecretTile& operator=(const SecretTile& _Other) = delete;
	SecretTile& operator=(SecretTile&& _Other) noexcept = delete;

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
