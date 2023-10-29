#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss_OldCrowDefinition.cpp"

class Boss_OldCrowSmallCrow : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_OldCrowSmallCrow();
	~Boss_OldCrowSmallCrow();

	// delete Function
	Boss_OldCrowSmallCrow(const Boss_OldCrowSmallCrow& _Other) = delete;
	Boss_OldCrowSmallCrow(Boss_OldCrowSmallCrow&& _Other) noexcept = delete;
	Boss_OldCrowSmallCrow& operator=(const Boss_OldCrowSmallCrow& _Other) = delete;
	Boss_OldCrowSmallCrow& operator=(Boss_OldCrowSmallCrow&& _Other) noexcept = delete;

	void SetSmallCrow(float4 _Pos, float4 _Rot);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentFBXRenderer> Renderer = nullptr;
	std::shared_ptr<class PhysXSphereComponent> m_pSphereComp = nullptr;

	float4 TargetPosition = float4::ZERO;

	float Angle = 0.0f; //공전할 트랜스폼의 각도 값

	void SetLerpDirection(float _DeltaTime);
	void SetDirection();
	void SetTargetTransform(float _DeltaTime);

	float4 CurrentDir = float4::ZERO;
	float4 Dir = float4::ZERO;

};

