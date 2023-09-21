#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� :
class CapsulTestActor : public GameEngineActor
{
public:
	// constrcuter destructer
	CapsulTestActor();
	~CapsulTestActor();

	// delete Function
	CapsulTestActor(const CapsulTestActor& _Other) = delete;
	CapsulTestActor(CapsulTestActor&& _Other) noexcept = delete;
	CapsulTestActor& operator=(const CapsulTestActor& _Other) = delete;
	CapsulTestActor& operator=(CapsulTestActor&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

