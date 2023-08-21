#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineNetObject.h>
#include <GameEngineCore/GameEngineNetActor.h>
// Ό³Έν :
class TestObject : public GameEngineNetActor
{
public:
	static TestObject* MainTestObject;
	// constrcuter destructer
	TestObject();
	~TestObject();

	// delete Function
	TestObject(const TestObject& _Other) = delete;
	TestObject(TestObject&& _Other) noexcept = delete;
	TestObject& operator=(const TestObject& _Other) = delete;
	TestObject& operator=(TestObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void UserUpdate(float _DeltaTime);
	void NetUpdate(float _DeltaTime);
	//void ServerUpdate(float _DeltaTime);

	void SendNetPacket(float _DeltaTime) override;

private:

	float m_pSpeed = 200.0f;
};

