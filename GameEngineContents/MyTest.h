#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MyTest : public GameEngineActor
{

public:

	MyTest();
	~MyTest();

	MyTest(const MyTest& _Other) = delete;
	MyTest(MyTest&& _Other) noexcept = delete;
	MyTest& operator=(const MyTest& _Other) = delete;
	MyTest& operator=(MyTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	
	void TestRender();

	void CreateKey();
	std::shared_ptr<class ParticleRenderer> Partcle = nullptr;
	
	std::shared_ptr<GameEngineFBXRenderer> New = nullptr;

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> MyUnits;

	std::shared_ptr<GameEngineRenderTarget> Target1 = nullptr;
	std::shared_ptr<GameEngineRenderTarget> Target2 = nullptr;

	std::function<bool(const std::string_view&, float, float)> UpdateFunc = nullptr;

	std::shared_ptr<GameEngineFBXRenderer> TestRenderer = nullptr;
	std::shared_ptr<GameEngineRenderer> TestRenderUnit = nullptr;
};

