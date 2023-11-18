#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class ExplainLevel : public ContentLevel
{
public:
	// constrcuter destructer
	ExplainLevel();
	~ExplainLevel();

	// delete Function
	ExplainLevel(const ExplainLevel& _Other) = delete;
	ExplainLevel(ExplainLevel&& _Other) noexcept = delete;
	ExplainLevel& operator=(const ExplainLevel& _Other) = delete;
	ExplainLevel& operator=(ExplainLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	void Create_Object();
	void Create_Enemy();

	float4 m_f4CameraRot = float4{ 45.0f , 0 , 0 };
	float4 m_f4CameraPos = float4{ 0, 0, 0 };
	float4 m_f4CameraPos = float4{ 2800 , 2500 , -6500 };

	GameEngineSoundPlayer MainBGM;
};
