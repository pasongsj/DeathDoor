#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossFrogBomb : public GameEngineActor
{
	friend class BossFrogFat;
public:
	// constrcuter destructer
	BossFrogBomb();
	~BossFrogBomb();

	// delete Function
	BossFrogBomb(const BossFrogBomb& _Other) = delete;
	BossFrogBomb(BossFrogBomb&& _Other) noexcept = delete;
	BossFrogBomb& operator=(const BossFrogBomb& _Other) = delete;
	BossFrogBomb& operator=(BossFrogBomb&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void SetTargetTile(const float4& _Start, const float4& _Target);
	void CreateDustParticle();

	std::shared_ptr<class ContentFBXRenderer> BombRender = nullptr;
	float4 Startpoint = float4::ZERO;
	float4 P2 = float4::ZERO;
	float4 Target = float4::ZERO;
};

