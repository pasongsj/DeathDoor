#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Start_BackGround : public GameEngineActor
{

public:

	Start_BackGround();
	~Start_BackGround();

	Start_BackGround(const Start_BackGround& _Other) = delete;
	Start_BackGround(Start_BackGround&& _Other) noexcept = delete;
	Start_BackGround& operator=(const Start_BackGround& _Other) = delete;
	Start_BackGround& operator=(Start_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void MoveCamera(float _DeltaTime);
	float Angle = 0.0f;

	std::shared_ptr<class ContentFBXRenderer> BakcGround = nullptr;

	std::shared_ptr<class ContentFBXRenderer> Hall_Crow_1 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> Hall_Crow_2 = nullptr;
	std::shared_ptr<class ContentFBXRenderer> Hall_Crow_3 = nullptr;

	std::shared_ptr<class ContentFBXRenderer> Hall_Banker = nullptr;

	std::shared_ptr<class ContentFBXRenderer> Book = nullptr;
};

