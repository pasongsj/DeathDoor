#pragma once
#include <GameEngineBase/GameEnginePacket.h>
#include <GameEngineCore/GameEngineTransform.h>

// 설명 : 넌 0번 플레이어야
//        넌 1번 플레이어야
class ConnectIDPacket : public GameEnginePacket
{
public:
	// constrcuter destructer
	ConnectIDPacket();
	~ConnectIDPacket();

	// delete Function
	ConnectIDPacket(const ConnectIDPacket& _Other) = delete;
	ConnectIDPacket(ConnectIDPacket&& _Other) noexcept = delete;
	ConnectIDPacket& operator=(const ConnectIDPacket& _Other) = delete;
	ConnectIDPacket& operator=(ConnectIDPacket&& _Other) noexcept = delete;

protected:

private:
};

