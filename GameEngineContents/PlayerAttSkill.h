#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Player.h"

// Ό³Έν :
class PlayerAttSkill : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	PlayerAttSkill();
	~PlayerAttSkill();

	// delete Function
	PlayerAttSkill(const PlayerAttSkill& _Other) = delete;
	PlayerAttSkill(PlayerAttSkill&& _Other) noexcept = delete;
	PlayerAttSkill& operator=(const PlayerAttSkill& _Other) = delete;
	PlayerAttSkill& operator=(PlayerAttSkill&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void Init();

private:

	std::shared_ptr<class ContentsRenderer> SkillRender = nullptr;
	std::shared_ptr<class PhysXSphereComponent> PhysXComp = nullptr;

	float4 Dir = float4::ZERO;
	float firetime = 0.0f;

	bool isShoot = false;


};

