#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Map_Office : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_Office();
	~Map_Office();

	// delete Function
	Map_Office(const Map_Office& _Other) = delete;
	Map_Office(Map_Office&& _Other) noexcept = delete;
	Map_Office& operator=(const Map_Office& _Other) = delete;
	Map_Office& operator=(Map_Office&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class PhysXBoxComponent> m_pBoxComp = nullptr;
	std::shared_ptr<GameEngineFBXRenderer> m_pRenderer = nullptr;
};
