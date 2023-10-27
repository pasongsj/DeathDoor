#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss_OldCrowDefinition.cpp"

class Boss_OldCrowCrowHead : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_OldCrowCrowHead();
	~Boss_OldCrowCrowHead();

	// delete Function
	Boss_OldCrowCrowHead(const Boss_OldCrowCrowHead& _Other) = delete;
	Boss_OldCrowCrowHead(Boss_OldCrowCrowHead&& _Other) noexcept = delete;
	Boss_OldCrowCrowHead& operator=(const Boss_OldCrowCrowHead& _Other) = delete;
	Boss_OldCrowCrowHead& operator=(Boss_OldCrowCrowHead&& _Other) noexcept = delete;

	void SetCrowHead(float4 _Pos, float4 _Rot);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentFBXRenderer> Renderer = nullptr;
	std::shared_ptr<class PhysXSphereComponent> m_pSphereComp = nullptr;

	void SetLerpDirection(float _DeltaTime);
	void AttackCheck();
	float4 GetPlayerDir();

	float4 CurrentDir = float4::ZERO;
	float4 Dir = float4::ZERO;

	bool IsAttacked = false; //플레이어의 공격을 받으면 플레이어가 바라보고 있는 방향으로 날아감.

	//float Angle = 0.0f;
};

