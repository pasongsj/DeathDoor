#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerAttackTrail : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	PlayerAttackTrail();
	~PlayerAttackTrail();

	// delete Function
	PlayerAttackTrail(const PlayerAttackTrail& _Other) = delete;
	PlayerAttackTrail(PlayerAttackTrail&& _Other) noexcept = delete;
	PlayerAttackTrail& operator=(const PlayerAttackTrail& _Other) = delete;
	PlayerAttackTrail& operator=(PlayerAttackTrail&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;

private:

	float EraseTime = 0.0f;

	void CreateTrail(float4 _Dir, float4 _Pos,bool isRightAttack, bool IsBasic = true);
	std::shared_ptr<class SwordTrailRenderer> TrailRenderer = nullptr;

};

