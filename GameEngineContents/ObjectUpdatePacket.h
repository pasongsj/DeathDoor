#pragma once
#include <GameEngineBase/GameEnginePacket.h>
#include <GameEngineCore/GameEngineTransform.h>

// Ό³Έν :
class ObjectUpdatePacket : public GameEnginePacket
{
public:
	// constrcuter destructer
	ObjectUpdatePacket();
	~ObjectUpdatePacket();

	// delete Function
	ObjectUpdatePacket(const ObjectUpdatePacket& _Other) = delete;
	ObjectUpdatePacket(ObjectUpdatePacket&& _Other) noexcept = delete;
	ObjectUpdatePacket& operator=(const ObjectUpdatePacket& _Other) = delete;
	ObjectUpdatePacket& operator=(ObjectUpdatePacket&& _Other) noexcept = delete;

protected:

private:
	float4 Pos;
	int Att;
	int Hp;
	int Animation;
	// TransformData Data;
};

