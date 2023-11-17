#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Boss_OldCrowDefinition.cpp"

class Boss_OldCrowEgg : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_OldCrowEgg();
	~Boss_OldCrowEgg();

	// delete Function
	Boss_OldCrowEgg(const Boss_OldCrowEgg& _Other) = delete;
	Boss_OldCrowEgg(Boss_OldCrowEgg&& _Other) noexcept = delete;
	Boss_OldCrowEgg& operator=(const Boss_OldCrowEgg& _Other) = delete;
	Boss_OldCrowEgg& operator=(Boss_OldCrowEgg&& _Other) noexcept = delete;

	void SetCrowEgg(float4 _Pos, float4 _Rot, float4 _Dir);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentFBXRenderer> Renderer = nullptr;
	std::shared_ptr<class PhysXSphereComponent> m_pSphereComp = nullptr;

	std::shared_ptr<class GameEngineActor> PentagramPivot = nullptr;

	std::shared_ptr<class Content2DRenderer> PentagramRenderer1;
	std::shared_ptr<class Content2DRenderer> PentagramRenderer2;

	float4 Dir = float4::ZERO;

	float PentagramScale = 0.0f;
	float ScaleValue = 1.0f;

	bool IsGround = false;
	bool IsEnd = false;

	void SetPentagramEffect(float _DeltaTime);
};

