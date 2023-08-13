#pragma once
#include <GameEngineBase/GameEnginePacket.h>
#include <GameEngineCore/GameEngineTransform.h>

// Ό³Έν :
class ObjectUpdatePacket : public GameEnginePacket
{
public:
	// constrcuter destructer
	ObjectUpdatePacket()
	{
		SetPacketID(PacketEnum::ObjectUpdatePacket);
	}
	~ObjectUpdatePacket()
	{
	}

protected:

private:
	float4 Pos;
	int Att;
	int Hp;
	int Animation;
	// TransformData Data;
};

