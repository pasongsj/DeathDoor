#pragma once
#include "GameEngineSerializer.h"
#include <memory>

// 설명 :
class GameEnginePacket : public std::enable_shared_from_this<GameEnginePacket>
{
public:
	// constrcuter destructer
	GameEnginePacket();
	~GameEnginePacket();

	// delete Function
	GameEnginePacket(const GameEnginePacket& _Other) = delete;
	GameEnginePacket(GameEnginePacket&& _Other) noexcept = delete;
	GameEnginePacket& operator=(const GameEnginePacket& _Other) = delete;
	GameEnginePacket& operator=(GameEnginePacket&& _Other) noexcept = delete;

protected:

private:
	unsigned int PacketID = -1; // <= 종류인데 int로 처리한다.
	unsigned int Size = -1; // <= 패킷의 크기
	unsigned int ObjectID = -1; // <= 어떤 오브젝트가 보냈다.

};
