#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Boomerang : public GameEngineActor
{
public:

	Boomerang();
	~Boomerang();

	Boomerang(const Boomerang& _Other) = delete;
	Boomerang(Boomerang&& _Other) noexcept = delete;
	Boomerang& operator=(const Boomerang& _Other) = delete;
	Boomerang& operator=(Boomerang&& _Other) noexcept = delete;

	enum class BoomerType
	{
		HEAD,
		LEFT,
		RIGHT,
		MAX
	};

	void SetBoomer(BoomerType Type, const float4& Position, const float4& Rotation);


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


	std::shared_ptr<class ContentFBXRenderer> AttackRenderer = nullptr;


};

