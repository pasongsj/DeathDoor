#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FireObject : public GameEngineActor
{

public:

	FireObject();
	~FireObject();

	FireObject(const FireObject& _Other) = delete;
	FireObject(FireObject&& _Other) noexcept = delete;
	FireObject& operator=(const FireObject& _Other) = delete;
	FireObject& operator=(FireObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	struct ScrollSpeeds
	{
		float ScrollSpeed_1 = 0.65f;
		float ScrollSpeed_2 = 1.05f;
		float ScrollSpeed_3 = 1.15f;
	};

	struct Scales
	{
		float Scale_1 = 1.0f;
		float Scale_2 = 1.0f;
		float Scale_3 = 1.0f;
	};

	struct FireNoise
	{
		float FrameTime = 0.0f;
		ScrollSpeeds ScrollSpeed;
		Scales Scale;
		float Padding = 0.0f;
	};

	struct DistortionXY
	{
		float DistortionX;
		float DistortionY;
	};

	struct Distortion
	{
		DistortionXY Distortion1;
		DistortionXY Distortion2;
		DistortionXY Distortion3;

		float DistortionScale = 0.8f;
		float DistortionBias = 0.5f;
	};

private:
	std::shared_ptr<class ContentSpriteRenderer> FireFront = nullptr;
	std::shared_ptr<class ContentSpriteRenderer> FireBack = nullptr;

	FireNoise NoiseData;
	Distortion DistortionData;
};

